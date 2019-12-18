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
typedef  int /*<<< orphan*/  acl_perm_t ;
typedef  int /*<<< orphan*/  acl_entry_t ;

/* Variables and functions */
 int _nfs4_parse_access_mask (char*,int /*<<< orphan*/ *) ; 
 int acl_set_permset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
parse_access_mask(char *str, acl_entry_t entry)
{
	int error;
	acl_perm_t perm;

	error = _nfs4_parse_access_mask(str, &perm);
	if (error)
		return (error);

	error = acl_set_permset(entry, &perm);

	return (error);
}