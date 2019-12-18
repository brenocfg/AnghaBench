#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_4__ {int /*<<< orphan*/ * server; int /*<<< orphan*/ * client; } ;
typedef  TYPE_1__ kcm_ccache_data ;

/* Variables and functions */
 int /*<<< orphan*/  kcm_ccache_remove_creds_internal (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

krb5_error_code
kcm_zero_ccache_data_internal(krb5_context context,
			      kcm_ccache_data *cache)
{
    if (cache->client != NULL) {
	krb5_free_principal(context, cache->client);
	cache->client = NULL;
    }

    if (cache->server != NULL) {
	krb5_free_principal(context, cache->server);
	cache->server = NULL;
    }

    kcm_ccache_remove_creds_internal(context, cache);

    return 0;
}