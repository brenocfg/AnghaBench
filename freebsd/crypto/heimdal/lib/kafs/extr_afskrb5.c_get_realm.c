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
struct krb5_kafs_data {int /*<<< orphan*/  context; } ;
struct kafs_data {struct krb5_kafs_data* data; } ;
typedef  int /*<<< orphan*/  krb5_realm ;

/* Variables and functions */
 int /*<<< orphan*/  krb5_free_host_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_get_host_realm (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
get_realm(struct kafs_data *data, const char *host)
{
    struct krb5_kafs_data *d = data->data;
    krb5_realm *realms;
    char *r;
    if(krb5_get_host_realm(d->context, host, &realms))
	return NULL;
    r = strdup(realms[0]);
    krb5_free_host_realm(d->context, realms);
    return r;
}