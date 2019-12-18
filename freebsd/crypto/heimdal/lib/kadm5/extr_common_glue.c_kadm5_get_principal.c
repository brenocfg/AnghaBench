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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  kadm5_ret_t ;
typedef  int /*<<< orphan*/  kadm5_principal_ent_t ;

/* Variables and functions */
 int /*<<< orphan*/  __CALL (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  get_principal ; 

kadm5_ret_t
kadm5_get_principal(void *server_handle,
		    krb5_principal princ,
		    kadm5_principal_ent_t out,
		    uint32_t mask)
{
    return __CALL(get_principal, (server_handle, princ, out, mask));
}