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
struct sp_ctx {scalar_t__ sp_magic; int sp_side; int* sp_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ABORT (char*,int) ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ SP_CTX_MAGIC ; 
#define  SP_SIDE_CLIENT 130 
#define  SP_SIDE_SERVER 129 
#define  SP_SIDE_UNDEF 128 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (struct sp_ctx*) ; 

__attribute__((used)) static void
sp_close(void *ctx)
{
	struct sp_ctx *spctx = ctx;

	PJDLOG_ASSERT(spctx != NULL);
	PJDLOG_ASSERT(spctx->sp_magic == SP_CTX_MAGIC);

	switch (spctx->sp_side) {
	case SP_SIDE_UNDEF:
		PJDLOG_ASSERT(spctx->sp_fd[0] >= 0);
		close(spctx->sp_fd[0]);
		spctx->sp_fd[0] = -1;
		PJDLOG_ASSERT(spctx->sp_fd[1] >= 0);
		close(spctx->sp_fd[1]);
		spctx->sp_fd[1] = -1;
		break;
	case SP_SIDE_CLIENT:
		PJDLOG_ASSERT(spctx->sp_fd[0] >= 0);
		close(spctx->sp_fd[0]);
		spctx->sp_fd[0] = -1;
		PJDLOG_ASSERT(spctx->sp_fd[1] == -1);
		break;
	case SP_SIDE_SERVER:
		PJDLOG_ASSERT(spctx->sp_fd[1] >= 0);
		close(spctx->sp_fd[1]);
		spctx->sp_fd[1] = -1;
		PJDLOG_ASSERT(spctx->sp_fd[0] == -1);
		break;
	default:
		PJDLOG_ABORT("Invalid socket side (%d).", spctx->sp_side);
	}

	spctx->sp_magic = 0;
	free(spctx);
}