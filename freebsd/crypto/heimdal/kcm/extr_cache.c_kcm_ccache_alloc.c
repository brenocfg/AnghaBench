#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_7__ {int /*<<< orphan*/ * keytab; } ;
struct TYPE_8__ {int flags; int refcnt; int mode; int uid; int gid; int /*<<< orphan*/  mutex; scalar_t__ renew_life; scalar_t__ tkt_life; TYPE_1__ key; int /*<<< orphan*/ * creds; int /*<<< orphan*/ * server; int /*<<< orphan*/ * client; int /*<<< orphan*/ * name; int /*<<< orphan*/  uuid; struct TYPE_8__* next; } ;
typedef  TYPE_2__ kcm_ccache_data ;
typedef  TYPE_2__* kcm_ccache ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int KCM_FLAGS_VALID ; 
 scalar_t__ KRB5_CC_NOMEM ; 
 scalar_t__ KRB5_CC_WRITE ; 
 int /*<<< orphan*/  RAND_bytes (int /*<<< orphan*/ ,int) ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 TYPE_2__* ccache_head ; 
 int /*<<< orphan*/  ccache_mutex ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static krb5_error_code
kcm_ccache_alloc(krb5_context context,
		 const char *name,
		 kcm_ccache *ccache)
{
    kcm_ccache slot = NULL, p;
    krb5_error_code ret;
    int new_slot = 0;

    *ccache = NULL;

    /* First, check for duplicates */
    HEIMDAL_MUTEX_lock(&ccache_mutex);
    ret = 0;
    for (p = ccache_head; p != NULL; p = p->next) {
	if (p->flags & KCM_FLAGS_VALID) {
	    if (strcmp(p->name, name) == 0) {
		ret = KRB5_CC_WRITE;
		break;
	    }
	} else if (slot == NULL)
	    slot = p;
    }

    if (ret)
	goto out;

    /*
     * Create an enpty slot for us.
     */
    if (slot == NULL) {
	slot = (kcm_ccache_data *)malloc(sizeof(*slot));
	if (slot == NULL) {
	    ret = KRB5_CC_NOMEM;
	    goto out;
	}
	slot->next = ccache_head;
	HEIMDAL_MUTEX_init(&slot->mutex);
	new_slot = 1;
    }

    RAND_bytes(slot->uuid, sizeof(slot->uuid));

    slot->name = strdup(name);
    if (slot->name == NULL) {
	ret = KRB5_CC_NOMEM;
	goto out;
    }

    slot->refcnt = 1;
    slot->flags = KCM_FLAGS_VALID;
    slot->mode = S_IRUSR | S_IWUSR;
    slot->uid = -1;
    slot->gid = -1;
    slot->client = NULL;
    slot->server = NULL;
    slot->creds = NULL;
    slot->key.keytab = NULL;
    slot->tkt_life = 0;
    slot->renew_life = 0;

    if (new_slot)
	ccache_head = slot;

    *ccache = slot;

    HEIMDAL_MUTEX_unlock(&ccache_mutex);
    return 0;

out:
    HEIMDAL_MUTEX_unlock(&ccache_mutex);
    if (new_slot && slot != NULL) {
	HEIMDAL_MUTEX_destroy(&slot->mutex);
	free(slot);
    }
    return ret;
}