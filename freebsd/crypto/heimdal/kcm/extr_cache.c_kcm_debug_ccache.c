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
struct kcm_creds {struct kcm_creds* next; } ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_1__* kcm_ccache ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  name; int /*<<< orphan*/ * server; int /*<<< orphan*/ * client; struct kcm_creds* creds; struct TYPE_4__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  KCM_ASSERT_VALID (TYPE_1__*) ; 
 int KCM_FLAGS_VALID ; 
 TYPE_1__* ccache_head ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  kcm_log (int,char*,...) ; 
 int /*<<< orphan*/  krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**) ; 

krb5_error_code kcm_debug_ccache(krb5_context context)
{
    kcm_ccache p;

    for (p = ccache_head; p != NULL; p = p->next) {
	char *cpn = NULL, *spn = NULL;
	int ncreds = 0;
	struct kcm_creds *k;

	if ((p->flags & KCM_FLAGS_VALID) == 0) {
	    kcm_log(7, "cache %08x: empty slot");
	    continue;
	}

	KCM_ASSERT_VALID(p);

	for (k = p->creds; k != NULL; k = k->next)
	    ncreds++;

	if (p->client != NULL)
	    krb5_unparse_name(context, p->client, &cpn);
	if (p->server != NULL)
	    krb5_unparse_name(context, p->server, &spn);

	kcm_log(7, "cache %08x: name %s refcnt %d flags %04x mode %04o "
		"uid %d gid %d client %s server %s ncreds %d",
		p, p->name, p->refcnt, p->flags, p->mode, p->uid, p->gid,
		(cpn == NULL) ? "<none>" : cpn,
		(spn == NULL) ? "<none>" : spn,
		ncreds);

	if (cpn != NULL)
	    free(cpn);
	if (spn != NULL)
	    free(spn);
    }

    return 0;
}