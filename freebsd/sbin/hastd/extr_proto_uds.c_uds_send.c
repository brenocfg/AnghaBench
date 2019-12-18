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
struct uds_ctx {scalar_t__ uc_magic; scalar_t__ uc_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ UDS_CTX_MAGIC ; 
 int proto_common_send (scalar_t__,unsigned char const*,size_t,int) ; 

__attribute__((used)) static int
uds_send(void *ctx, const unsigned char *data, size_t size, int fd)
{
	struct uds_ctx *uctx = ctx;

	PJDLOG_ASSERT(uctx != NULL);
	PJDLOG_ASSERT(uctx->uc_magic == UDS_CTX_MAGIC);
	PJDLOG_ASSERT(uctx->uc_fd >= 0);

	return (proto_common_send(uctx->uc_fd, data, size, fd));
}