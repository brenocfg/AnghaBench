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
struct sp_ctx {int* sp_fd; int /*<<< orphan*/  sp_magic; int /*<<< orphan*/  sp_side; } ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  SP_CTX_MAGIC ; 
 int /*<<< orphan*/  SP_SIDE_CLIENT ; 
 int /*<<< orphan*/  SP_SIDE_SERVER ; 
 int errno ; 
 struct sp_ctx* malloc (int) ; 

__attribute__((used)) static int
sp_wrap(int fd, bool client, void **ctxp)
{
	struct sp_ctx *spctx;

	PJDLOG_ASSERT(fd >= 0);

	spctx = malloc(sizeof(*spctx));
	if (spctx == NULL)
		return (errno);

	if (client) {
		spctx->sp_side = SP_SIDE_CLIENT;
		spctx->sp_fd[0] = fd;
		spctx->sp_fd[1] = -1;
	} else {
		spctx->sp_side = SP_SIDE_SERVER;
		spctx->sp_fd[0] = -1;
		spctx->sp_fd[1] = fd;
	}
	spctx->sp_magic = SP_CTX_MAGIC;
	*ctxp = spctx;

	return (0);
}