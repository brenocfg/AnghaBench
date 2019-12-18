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
struct smbioc_flags {int ioc_level; int ioc_mask; int ioc_flags; } ;
struct smb_ctx {int ct_fd; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SMBIOC_SETFLAGS ; 
 int errno ; 
 int ioctl (int,int /*<<< orphan*/ ,struct smbioc_flags*) ; 

int
smb_ctx_setflags(struct smb_ctx *ctx, int level, int mask, int flags)
{
	struct smbioc_flags fl;

	if (ctx->ct_fd == -1)
		return EINVAL;
	fl.ioc_level = level;
	fl.ioc_mask = mask;
	fl.ioc_flags = flags;
	if (ioctl(ctx->ct_fd, SMBIOC_SETFLAGS, &fl) == -1)
		return errno;
	return 0;
}