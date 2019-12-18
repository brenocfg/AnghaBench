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
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 char* atf_tc_get_config_var (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  atf_tc_has_config_var (int /*<<< orphan*/  const*,char*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static __inline bool
atf_check_fstype(const atf_tc_t *tc, const char *fs)
{
	const char *fstype;

	if (!atf_tc_has_config_var(tc, "fstype"))
		return true;

	fstype = atf_tc_get_config_var(tc, "fstype");
	if (strcmp(fstype, fs) == 0)
		return true;
	return false;
}