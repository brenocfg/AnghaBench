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
typedef  int /*<<< orphan*/  str ;
typedef  scalar_t__ kadm5_ret_t ;

/* Variables and functions */
 scalar_t__ _kadm5_privs_to_string (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  context ; 
 scalar_t__ kadm5_get_privs (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  kadm_handle ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
get_privs(void *opt, int argc, char **argv)
{
    uint32_t privs;
    char str[128];
    kadm5_ret_t ret;

    ret = kadm5_get_privs(kadm_handle, &privs);
    if(ret)
	krb5_warn(context, ret, "kadm5_get_privs");
    else{
	ret =_kadm5_privs_to_string(privs, str, sizeof(str));
	if (ret == 0)
	    printf("%s\n", str);
	else
	    printf("privs: 0x%x\n", (unsigned int)privs);
    }
    return 0;
}