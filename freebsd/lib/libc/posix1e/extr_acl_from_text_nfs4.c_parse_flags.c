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
typedef  int /*<<< orphan*/  acl_flag_t ;
typedef  int /*<<< orphan*/  acl_entry_t ;

/* Variables and functions */
 int _nfs4_parse_flags (char*,int /*<<< orphan*/ *) ; 
 int acl_set_flagset_np (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
parse_flags(char *str, acl_entry_t entry)
{
	int error;
	acl_flag_t flags;

	error = _nfs4_parse_flags(str, &flags);
	if (error)
		return (error);

	error = acl_set_flagset_np(entry, &flags);

	return (error);
}