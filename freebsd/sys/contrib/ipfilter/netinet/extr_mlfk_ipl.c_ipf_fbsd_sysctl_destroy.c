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
 int ENOTEMPTY ; 
 int /*<<< orphan*/  ipf_clist ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ sysctl_ctx_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ipf_fbsd_sysctl_destroy(void)
{
	if (sysctl_ctx_free(&ipf_clist)) {
		printf("sysctl_ctx_free failed");
		return(ENOTEMPTY);
	}
	return 0;
}