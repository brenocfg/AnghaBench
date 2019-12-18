#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct io_thread_req {int length; int sectorsize; char* buffer; void* error; int /*<<< orphan*/ * fds; int /*<<< orphan*/  req; scalar_t__* offsets; scalar_t__ offset; int /*<<< orphan*/  sector_mask; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 void* BLK_STS_NOTSUPP ; 
#define  REQ_OP_DISCARD 131 
 int REQ_OP_FLUSH ; 
#define  REQ_OP_READ 130 
#define  REQ_OP_WRITE 129 
#define  REQ_OP_WRITE_ZEROES 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 void* map_error (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int os_falloc_punch (int /*<<< orphan*/ ,scalar_t__,unsigned long) ; 
 int os_pread_file (int /*<<< orphan*/ ,char*,unsigned long,scalar_t__) ; 
 int os_pwrite_file (int /*<<< orphan*/ ,char*,unsigned long,scalar_t__) ; 
 int os_sync_file (int /*<<< orphan*/ ) ; 
 int req_op (int /*<<< orphan*/ ) ; 
 int ubd_test_bit (int,unsigned char*) ; 
 void* update_bitmap (struct io_thread_req*) ; 

__attribute__((used)) static void do_io(struct io_thread_req *req)
{
	char *buf = NULL;
	unsigned long len;
	int n, nsectors, start, end, bit;
	__u64 off;

	/* FLUSH is really a special case, we cannot "case" it with others */

	if (req_op(req->req) == REQ_OP_FLUSH) {
		/* fds[0] is always either the rw image or our cow file */
		req->error = map_error(-os_sync_file(req->fds[0]));
		return;
	}

	nsectors = req->length / req->sectorsize;
	start = 0;
	do {
		bit = ubd_test_bit(start, (unsigned char *) &req->sector_mask);
		end = start;
		while((end < nsectors) &&
		      (ubd_test_bit(end, (unsigned char *)
				    &req->sector_mask) == bit))
			end++;

		off = req->offset + req->offsets[bit] +
			start * req->sectorsize;
		len = (end - start) * req->sectorsize;
		if (req->buffer != NULL)
			buf = &req->buffer[start * req->sectorsize];

		switch (req_op(req->req)) {
		case REQ_OP_READ:
			n = 0;
			do {
				buf = &buf[n];
				len -= n;
				n = os_pread_file(req->fds[bit], buf, len, off);
				if (n < 0) {
					req->error = map_error(-n);
					return;
				}
			} while((n < len) && (n != 0));
			if (n < len) memset(&buf[n], 0, len - n);
			break;
		case REQ_OP_WRITE:
			n = os_pwrite_file(req->fds[bit], buf, len, off);
			if(n != len){
				req->error = map_error(-n);
				return;
			}
			break;
		case REQ_OP_DISCARD:
		case REQ_OP_WRITE_ZEROES:
			n = os_falloc_punch(req->fds[bit], off, len);
			if (n) {
				req->error = map_error(-n);
				return;
			}
			break;
		default:
			WARN_ON_ONCE(1);
			req->error = BLK_STS_NOTSUPP;
			return;
		}

		start = end;
	} while(start < nsectors);

	req->error = update_bitmap(req);
}