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
struct TYPE_4__ {int /*<<< orphan*/  vtable; } ;
struct vectx {scalar_t__ vec_hashsz; int vec_off; TYPE_2__ vec_ctx; TYPE_1__* vec_md; int /*<<< orphan*/  vec_fd; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ *,unsigned char*,int) ;} ;

/* Variables and functions */
 int read (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,unsigned char*,int) ; 

ssize_t
vectx_read(struct vectx *ctx, void *buf, size_t nbytes)
{
	unsigned char *bp = buf;
	int n;
	size_t off;

	if (ctx->vec_hashsz == 0)	/* nothing to do */
		return (read(ctx->vec_fd, buf, nbytes));

	off = 0;
	do {
		n = read(ctx->vec_fd, &bp[off], nbytes - off);
		if (n < 0)
			return (n);
		if (n > 0) {
			ctx->vec_md->update(&ctx->vec_ctx.vtable, &bp[off], n);
			off += n;
			ctx->vec_off += n;
		}
	} while (n > 0 && off < nbytes);
	return (off);
}