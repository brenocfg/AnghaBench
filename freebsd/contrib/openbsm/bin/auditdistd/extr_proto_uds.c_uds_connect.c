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
struct uds_ctx {int /*<<< orphan*/  uc_sun; int /*<<< orphan*/  uc_fd; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  UDS_SIDE_CLIENT ; 
 int connect (int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int errno ; 
 int /*<<< orphan*/  uds_close (struct uds_ctx*) ; 
 int uds_common_setup (char const*,int /*<<< orphan*/ ,struct uds_ctx**) ; 

__attribute__((used)) static int
uds_connect(const char *srcaddr, const char *dstaddr, int timeout, void **ctxp)
{
	struct uds_ctx *uctx;
	int error;

	PJDLOG_ASSERT(dstaddr != NULL);
	PJDLOG_ASSERT(timeout >= -1);

	error = uds_common_setup(dstaddr, UDS_SIDE_CLIENT, &uctx);
	if (error != 0)
		return (error);

	PJDLOG_ASSERT(srcaddr == NULL);

	if (connect(uctx->uc_fd, (struct sockaddr *)&uctx->uc_sun,
	    sizeof(uctx->uc_sun)) == -1) {
		error = errno;
		uds_close(uctx);
		return (error);
	}

	*ctxp = uctx;

	return (0);
}