#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct rsocket {int state; size_t sbuf_bytes_avail; size_t target_sge; size_t sq_inline; void* sbuf; int /*<<< orphan*/  slock; TYPE_2__* ssgl; TYPE_1__* target_sgl; scalar_t__ iomap_pending; } ;
struct iovec {size_t iov_len; } ;
typedef  int ssize_t ;
struct TYPE_4__ {size_t addr; size_t length; } ;
struct TYPE_3__ {size_t length; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  ECONNRESET ; 
 scalar_t__ EINPROGRESS ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBV_SEND_INLINE ; 
 size_t RS_MAX_TRANSFER ; 
 size_t RS_OLAP_START_SIZE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fastlock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fastlock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idm ; 
 struct rsocket* idm_at (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rs_can_send (struct rsocket*) ; 
 int /*<<< orphan*/  rs_conn_can_send ; 
 int /*<<< orphan*/  rs_copy_iov (void*,struct iovec const**,size_t*,size_t) ; 
 int rs_do_connect (struct rsocket*) ; 
 int rs_get_comp (struct rsocket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_nonblocking (struct rsocket*,int) ; 
 int rs_opening ; 
 size_t rs_sbuf_left (struct rsocket*) ; 
 int rs_send_iomaps (struct rsocket*,int) ; 
 int rs_writable ; 
 int rs_write_data (struct rsocket*,TYPE_2__*,int,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t rsendv(int socket, const struct iovec *iov, int iovcnt, int flags)
{
	struct rsocket *rs;
	const struct iovec *cur_iov;
	size_t left, len, offset = 0;
	uint32_t xfer_size, olen = RS_OLAP_START_SIZE;
	int i, ret = 0;

	rs = idm_at(&idm, socket);
	if (rs->state & rs_opening) {
		ret = rs_do_connect(rs);
		if (ret) {
			if (errno == EINPROGRESS)
				errno = EAGAIN;
			return ret;
		}
	}

	cur_iov = iov;
	len = iov[0].iov_len;
	for (i = 1; i < iovcnt; i++)
		len += iov[i].iov_len;
	left = len;

	fastlock_acquire(&rs->slock);
	if (rs->iomap_pending) {
		ret = rs_send_iomaps(rs, flags);
		if (ret)
			goto out;
	}
	for (; left; left -= xfer_size) {
		if (!rs_can_send(rs)) {
			ret = rs_get_comp(rs, rs_nonblocking(rs, flags),
					  rs_conn_can_send);
			if (ret)
				break;
			if (!(rs->state & rs_writable)) {
				ret = ERR(ECONNRESET);
				break;
			}
		}

		if (olen < left) {
			xfer_size = olen;
			if (olen < RS_MAX_TRANSFER)
				olen <<= 1;
		} else {
			xfer_size = left;
		}

		if (xfer_size > rs->sbuf_bytes_avail)
			xfer_size = rs->sbuf_bytes_avail;
		if (xfer_size > rs->target_sgl[rs->target_sge].length)
			xfer_size = rs->target_sgl[rs->target_sge].length;

		if (xfer_size <= rs_sbuf_left(rs)) {
			rs_copy_iov((void *) (uintptr_t) rs->ssgl[0].addr,
				    &cur_iov, &offset, xfer_size);
			rs->ssgl[0].length = xfer_size;
			ret = rs_write_data(rs, rs->ssgl, 1, xfer_size,
					    xfer_size <= rs->sq_inline ? IBV_SEND_INLINE : 0);
			if (xfer_size < rs_sbuf_left(rs))
				rs->ssgl[0].addr += xfer_size;
			else
				rs->ssgl[0].addr = (uintptr_t) rs->sbuf;
		} else {
			rs->ssgl[0].length = rs_sbuf_left(rs);
			rs_copy_iov((void *) (uintptr_t) rs->ssgl[0].addr, &cur_iov,
				    &offset, rs->ssgl[0].length);
			rs->ssgl[1].length = xfer_size - rs->ssgl[0].length;
			rs_copy_iov(rs->sbuf, &cur_iov, &offset, rs->ssgl[1].length);
			ret = rs_write_data(rs, rs->ssgl, 2, xfer_size,
					    xfer_size <= rs->sq_inline ? IBV_SEND_INLINE : 0);
			rs->ssgl[0].addr = (uintptr_t) rs->sbuf + rs->ssgl[1].length;
		}
		if (ret)
			break;
	}
out:
	fastlock_release(&rs->slock);

	return (ret && left == len) ? ret : len - left;
}