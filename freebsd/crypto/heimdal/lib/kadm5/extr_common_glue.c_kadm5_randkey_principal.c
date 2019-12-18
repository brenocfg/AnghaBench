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
typedef  int /*<<< orphan*/  kadm5_ret_t ;

/* Variables and functions */
 int /*<<< orphan*/  __CALL (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  randkey_principal ; 

kadm5_ret_t
kadm5_randkey_principal(void *server_handle,
			krb5_principal princ,
			krb5_keyblock **new_keys,
			int *n_keys)
{
    return __CALL(randkey_principal, (server_handle, princ, new_keys, n_keys));
}