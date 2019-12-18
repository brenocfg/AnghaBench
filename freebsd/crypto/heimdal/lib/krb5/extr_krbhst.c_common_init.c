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
struct krb5_krbhst_data {int /*<<< orphan*/  hosts; int /*<<< orphan*/ * index; int /*<<< orphan*/ * end; int /*<<< orphan*/  flags; int /*<<< orphan*/ * realm; } ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  KD_CONFIG_EXISTS ; 
 int /*<<< orphan*/  KD_LARGE_MSG ; 
 int KRB5_KRBHST_FLAGS_LARGE_MSG ; 
 int /*<<< orphan*/  _krb5_debug (int /*<<< orphan*/ ,int,char*,char const*,char const*,int) ; 
 struct krb5_krbhst_data* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct krb5_krbhst_data*) ; 
 int /*<<< orphan*/  strchr (char const*,char) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static struct krb5_krbhst_data*
common_init(krb5_context context,
	    const char *service,
	    const char *realm,
	    int flags)
{
    struct krb5_krbhst_data *kd;

    if((kd = calloc(1, sizeof(*kd))) == NULL)
	return NULL;

    if((kd->realm = strdup(realm)) == NULL) {
	free(kd);
	return NULL;
    }

    _krb5_debug(context, 2, "Trying to find service %s for realm %s flags %x",
		service, realm, flags);

    /* For 'realms' without a . do not even think of going to DNS */
    if (!strchr(realm, '.'))
	kd->flags |= KD_CONFIG_EXISTS;

    if (flags & KRB5_KRBHST_FLAGS_LARGE_MSG)
	kd->flags |= KD_LARGE_MSG;
    kd->end = kd->index = &kd->hosts;
    return kd;
}