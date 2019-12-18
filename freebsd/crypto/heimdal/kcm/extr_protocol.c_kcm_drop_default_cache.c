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
struct kcm_default_cache {struct kcm_default_cache* name; struct kcm_default_cache* next; int /*<<< orphan*/  session; int /*<<< orphan*/  uid; } ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  kcm_client ;

/* Variables and functions */
 struct kcm_default_cache* default_caches ; 
 int /*<<< orphan*/  free (struct kcm_default_cache*) ; 
 int /*<<< orphan*/  kcm_is_same_session (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (struct kcm_default_cache*,char*) ; 

__attribute__((used)) static void
kcm_drop_default_cache(krb5_context context, kcm_client *client, char *name)
{
    struct kcm_default_cache **c;

    for (c = &default_caches; *c != NULL; c = &(*c)->next) {
	if (!kcm_is_same_session(client, (*c)->uid, (*c)->session))
	    continue;
	if (strcmp((*c)->name, name) == 0) {
	    struct kcm_default_cache *h = *c;
	    *c = (*c)->next;
	    free(h->name);
	    free(h);
	    break;
	}
    }
}