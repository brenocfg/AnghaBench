#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kcm_creds {struct kcm_creds* next; int /*<<< orphan*/  cred; } ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_1__* kcm_ccache ;
struct TYPE_3__ {struct kcm_creds* creds; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct kcm_creds*) ; 
 int /*<<< orphan*/  krb5_free_cred_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

krb5_error_code
kcm_ccache_remove_creds_internal(krb5_context context,
				 kcm_ccache ccache)
{
    struct kcm_creds *k;

    k = ccache->creds;
    while (k != NULL) {
	struct kcm_creds *old;

	krb5_free_cred_contents(context, &k->cred);
	old = k;
	k = k->next;
	free(old);
    }
    ccache->creds = NULL;

    return 0;
}