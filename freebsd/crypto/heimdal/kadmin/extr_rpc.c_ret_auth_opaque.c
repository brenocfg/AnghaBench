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
struct opaque_auth {int /*<<< orphan*/  data; int /*<<< orphan*/  flavor; } ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;

/* Variables and functions */
 scalar_t__ krb5_ret_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ret_data_xdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
ret_auth_opaque(krb5_storage *msg, struct opaque_auth *ao)
{
    krb5_error_code ret;
    ret = krb5_ret_uint32(msg, &ao->flavor);
    if (ret) return ret;
    ret = ret_data_xdr(msg, &ao->data);
    return ret;
}