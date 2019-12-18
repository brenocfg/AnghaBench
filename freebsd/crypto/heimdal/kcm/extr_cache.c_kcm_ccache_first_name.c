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
typedef  int /*<<< orphan*/  kcm_client ;
typedef  TYPE_1__* kcm_ccache ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  session; int /*<<< orphan*/  uid; struct TYPE_3__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* ccache_head ; 
 int /*<<< orphan*/  ccache_mutex ; 
 scalar_t__ kcm_is_same_session (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

char *
kcm_ccache_first_name(kcm_client *client)
{
    kcm_ccache p;
    char *name = NULL;

    HEIMDAL_MUTEX_lock(&ccache_mutex);

    for (p = ccache_head; p != NULL; p = p->next) {
	if (kcm_is_same_session(client, p->uid, p->session))
	    break;
    }
    if (p)
	name = strdup(p->name);
    HEIMDAL_MUTEX_unlock(&ccache_mutex);
    return name;
}