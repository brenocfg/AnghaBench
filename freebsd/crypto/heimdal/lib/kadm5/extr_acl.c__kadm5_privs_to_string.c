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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  kadm5_ret_t ;

/* Variables and functions */
 scalar_t__ acl_units ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  unparse_flags (scalar_t__,scalar_t__,char*,size_t) ; 

kadm5_ret_t
_kadm5_privs_to_string(uint32_t privs, char *string, size_t len)
{
    if(privs == 0)
	strlcpy(string, "none", len);
    else
	unparse_flags(privs, acl_units + 1, string, len);
    return 0;
}