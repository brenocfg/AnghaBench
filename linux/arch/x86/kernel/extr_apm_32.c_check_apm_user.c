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
struct apm_user {scalar_t__ magic; } ;

/* Variables and functions */
 scalar_t__ APM_BIOS_MAGIC ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 

__attribute__((used)) static int check_apm_user(struct apm_user *as, const char *func)
{
	if (as == NULL || as->magic != APM_BIOS_MAGIC) {
		pr_err("%s passed bad filp\n", func);
		return 1;
	}
	return 0;
}