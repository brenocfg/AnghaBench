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
struct sshbuf {int refcount; scalar_t__ alloc; int /*<<< orphan*/ * d; int /*<<< orphan*/ * cd; scalar_t__ size; scalar_t__ off; scalar_t__ readonly; } ;

/* Variables and functions */
 scalar_t__ SSHBUF_SIZE_INIT ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * recallocarray (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  sshbuf_check_sanity (struct sshbuf*) ; 

void
sshbuf_reset(struct sshbuf *buf)
{
	u_char *d;

	if (buf->readonly || buf->refcount > 1) {
		/* Nonsensical. Just make buffer appear empty */
		buf->off = buf->size;
		return;
	}
	(void) sshbuf_check_sanity(buf);
	buf->off = buf->size = 0;
	if (buf->alloc != SSHBUF_SIZE_INIT) {
		if ((d = recallocarray(buf->d, buf->alloc, SSHBUF_SIZE_INIT,
		    1)) != NULL) {
			buf->cd = buf->d = d;
			buf->alloc = SSHBUF_SIZE_INIT;
		}
	}
	explicit_bzero(buf->d, SSHBUF_SIZE_INIT);
}