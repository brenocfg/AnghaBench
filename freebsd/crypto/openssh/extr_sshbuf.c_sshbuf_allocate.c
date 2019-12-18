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
typedef  int /*<<< orphan*/  u_char ;
struct sshbuf {size_t size; size_t max_size; size_t alloc; int /*<<< orphan*/ * d; int /*<<< orphan*/ * cd; } ;

/* Variables and functions */
 size_t ROUNDUP (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSHBUF_DBG (char*) ; 
 int /*<<< orphan*/  SSHBUF_SIZE_INC ; 
 int /*<<< orphan*/  SSHBUF_TELL (char*) ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int /*<<< orphan*/ * recallocarray (int /*<<< orphan*/ *,size_t,size_t,int) ; 
 int sshbuf_check_reserve (struct sshbuf*,size_t) ; 
 int /*<<< orphan*/  sshbuf_maybe_pack (struct sshbuf*,int) ; 

int
sshbuf_allocate(struct sshbuf *buf, size_t len)
{
	size_t rlen, need;
	u_char *dp;
	int r;

	SSHBUF_DBG(("allocate buf = %p len = %zu", buf, len));
	if ((r = sshbuf_check_reserve(buf, len)) != 0)
		return r;
	/*
	 * If the requested allocation appended would push us past max_size
	 * then pack the buffer, zeroing buf->off.
	 */
	sshbuf_maybe_pack(buf, buf->size + len > buf->max_size);
	SSHBUF_TELL("allocate");
	if (len + buf->size <= buf->alloc)
		return 0; /* already have it. */

	/*
	 * Prefer to alloc in SSHBUF_SIZE_INC units, but
	 * allocate less if doing so would overflow max_size.
	 */
	need = len + buf->size - buf->alloc;
	rlen = ROUNDUP(buf->alloc + need, SSHBUF_SIZE_INC);
	SSHBUF_DBG(("need %zu initial rlen %zu", need, rlen));
	if (rlen > buf->max_size)
		rlen = buf->alloc + need;
	SSHBUF_DBG(("adjusted rlen %zu", rlen));
	if ((dp = recallocarray(buf->d, buf->alloc, rlen, 1)) == NULL) {
		SSHBUF_DBG(("realloc fail"));
		return SSH_ERR_ALLOC_FAIL;
	}
	buf->alloc = rlen;
	buf->cd = buf->d = dp;
	if ((r = sshbuf_check_reserve(buf, len)) < 0) {
		/* shouldn't fail */
		return r;
	}
	SSHBUF_TELL("done");
	return 0;
}