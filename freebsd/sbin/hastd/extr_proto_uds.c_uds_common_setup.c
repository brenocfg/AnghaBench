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
struct uds_ctx {int uc_fd; int uc_side; int /*<<< orphan*/  uc_magic; scalar_t__ uc_owner; int /*<<< orphan*/  uc_sun; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  UDS_CTX_MAGIC ; 
 int errno ; 
 int /*<<< orphan*/  free (struct uds_ctx*) ; 
 struct uds_ctx* malloc (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uds_addr (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
uds_common_setup(const char *addr, void **ctxp, int side)
{
	struct uds_ctx *uctx;
	int ret;

	uctx = malloc(sizeof(*uctx));
	if (uctx == NULL)
		return (errno);

	/* Parse given address. */
	if ((ret = uds_addr(addr, &uctx->uc_sun)) != 0) {
		free(uctx);
		return (ret);
	}

	uctx->uc_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (uctx->uc_fd == -1) {
		ret = errno;
		free(uctx);
		return (ret);
	}

	uctx->uc_side = side;
	uctx->uc_owner = 0;
	uctx->uc_magic = UDS_CTX_MAGIC;
	*ctxp = uctx;

	return (0);
}