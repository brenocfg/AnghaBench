#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  TYPE_1__* kcm_ccache ;
struct TYPE_5__ {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 TYPE_1__* KCMCACHE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KCM_ASSERT_VALID (TYPE_1__*) ; 
 scalar_t__ kcm_zero_ccache_data_internal (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ krb5_copy_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
kcmss_initialize(krb5_context context,
		 krb5_ccache id,
		 krb5_principal primary_principal)
{
    krb5_error_code ret;
    kcm_ccache c = KCMCACHE(id);

    KCM_ASSERT_VALID(c);

    ret = kcm_zero_ccache_data_internal(context, c);
    if (ret)
	return ret;

    ret = krb5_copy_principal(context, primary_principal,
			      &c->client);

    return ret;
}