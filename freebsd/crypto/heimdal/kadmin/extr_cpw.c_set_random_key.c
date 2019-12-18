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
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  int krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int kadm5_randkey_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  kadm_handle ; 
 int /*<<< orphan*/  krb5_free_keyblock_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
set_random_key (krb5_principal principal)
{
    krb5_error_code ret;
    int i;
    krb5_keyblock *keys;
    int num_keys;

    ret = kadm5_randkey_principal(kadm_handle, principal, &keys, &num_keys);
    if(ret)
	return ret;
    for(i = 0; i < num_keys; i++)
	krb5_free_keyblock_contents(context, &keys[i]);
    free(keys);
    return 0;
}