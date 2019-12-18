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
struct uds_ctx {scalar_t__ uc_magic; scalar_t__ uc_side; scalar_t__ uc_fd; int /*<<< orphan*/  uc_sun; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ UDS_CTX_MAGIC ; 
 scalar_t__ UDS_SIDE_CLIENT ; 
 int connect (scalar_t__,struct sockaddr*,int) ; 
 int errno ; 

__attribute__((used)) static int
uds_connect(void *ctx, int timeout)
{
	struct uds_ctx *uctx = ctx;

	PJDLOG_ASSERT(uctx != NULL);
	PJDLOG_ASSERT(uctx->uc_magic == UDS_CTX_MAGIC);
	PJDLOG_ASSERT(uctx->uc_side == UDS_SIDE_CLIENT);
	PJDLOG_ASSERT(uctx->uc_fd >= 0);
	PJDLOG_ASSERT(timeout >= -1);

	if (connect(uctx->uc_fd, (struct sockaddr *)&uctx->uc_sun,
	    sizeof(uctx->uc_sun)) == -1) {
		return (errno);
	}

	return (0);
}