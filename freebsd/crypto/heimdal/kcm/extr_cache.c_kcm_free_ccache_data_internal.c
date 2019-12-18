#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_6__ {int /*<<< orphan*/  keyblock; int /*<<< orphan*/ * keytab; } ;
struct TYPE_7__ {int flags; int uid; int gid; int session; int /*<<< orphan*/  mutex; scalar_t__ refcnt; int /*<<< orphan*/ * next; scalar_t__ renew_life; scalar_t__ tkt_life; scalar_t__ mode; TYPE_1__ key; int /*<<< orphan*/ * name; } ;
typedef  TYPE_2__ kcm_ccache_data ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KCM_ASSERT_VALID (TYPE_2__*) ; 
 int KCM_FLAGS_USE_CACHED_KEY ; 
 int KCM_FLAGS_USE_KEYTAB ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcm_zero_ccache_data_internal (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_free_keyblock_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_keyblock_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_kt_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
kcm_free_ccache_data_internal(krb5_context context,
			      kcm_ccache_data *cache)
{
    KCM_ASSERT_VALID(cache);

    if (cache->name != NULL) {
	free(cache->name);
	cache->name = NULL;
    }

    if (cache->flags & KCM_FLAGS_USE_KEYTAB) {
	krb5_kt_close(context, cache->key.keytab);
	cache->key.keytab = NULL;
    } else if (cache->flags & KCM_FLAGS_USE_CACHED_KEY) {
	krb5_free_keyblock_contents(context, &cache->key.keyblock);
	krb5_keyblock_zero(&cache->key.keyblock);
    }

    cache->flags = 0;
    cache->mode = 0;
    cache->uid = -1;
    cache->gid = -1;
    cache->session = -1;

    kcm_zero_ccache_data_internal(context, cache);

    cache->tkt_life = 0;
    cache->renew_life = 0;

    cache->next = NULL;
    cache->refcnt = 0;

    HEIMDAL_MUTEX_unlock(&cache->mutex);
    HEIMDAL_MUTEX_destroy(&cache->mutex);
}