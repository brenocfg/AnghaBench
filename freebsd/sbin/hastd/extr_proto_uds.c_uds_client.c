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

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDS_SIDE_CLIENT ; 
 int uds_common_setup (char const*,void**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uds_client(const char *srcaddr, const char *dstaddr, void **ctxp)
{
	int ret;

	ret = uds_common_setup(dstaddr, ctxp, UDS_SIDE_CLIENT);
	if (ret != 0)
		return (ret);

	PJDLOG_ASSERT(srcaddr == NULL);

	return (0);
}