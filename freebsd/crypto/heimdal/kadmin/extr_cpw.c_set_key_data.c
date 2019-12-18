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
typedef  int /*<<< orphan*/  krb5_key_data ;
typedef  int krb5_error_code ;

/* Variables and functions */
 int kadm5_chpass_principal_with_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kadm_handle ; 

__attribute__((used)) static int
set_key_data (krb5_principal principal, krb5_key_data *key_data)
{
    krb5_error_code ret;

    ret = kadm5_chpass_principal_with_key (kadm_handle, principal,
					   3, key_data);
    return ret;
}