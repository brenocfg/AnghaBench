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
struct sp_ctx {int /*<<< orphan*/  sp_magic; int /*<<< orphan*/  sp_side; int /*<<< orphan*/  sp_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_UNIX ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SP_CTX_MAGIC ; 
 int /*<<< orphan*/  SP_SIDE_UNDEF ; 
 int errno ; 
 int /*<<< orphan*/  free (struct sp_ctx*) ; 
 struct sp_ctx* malloc (int) ; 
 int socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
sp_client(const char *srcaddr, const char *dstaddr, void **ctxp)
{
	struct sp_ctx *spctx;
	int ret;

	if (strcmp(dstaddr, "socketpair://") != 0)
		return (-1);

	PJDLOG_ASSERT(srcaddr == NULL);

	spctx = malloc(sizeof(*spctx));
	if (spctx == NULL)
		return (errno);

	if (socketpair(PF_UNIX, SOCK_STREAM, 0, spctx->sp_fd) == -1) {
		ret = errno;
		free(spctx);
		return (ret);
	}

	spctx->sp_side = SP_SIDE_UNDEF;
	spctx->sp_magic = SP_CTX_MAGIC;
	*ctxp = spctx;

	return (0);
}