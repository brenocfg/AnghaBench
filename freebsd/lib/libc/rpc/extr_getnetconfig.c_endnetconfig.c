#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct netconfig_vars {scalar_t__ valid; struct netconfig_vars* linep; struct netconfig_vars* ncp; struct netconfig_vars* nc_lookups; struct netconfig_vars* next; int /*<<< orphan*/ * nc_configs; scalar_t__ flag; } ;
struct netconfig_list {scalar_t__ valid; struct netconfig_list* linep; struct netconfig_list* ncp; struct netconfig_list* nc_lookups; struct netconfig_list* next; int /*<<< orphan*/ * nc_configs; scalar_t__ flag; } ;
struct TYPE_2__ {scalar_t__ ref; scalar_t__ eof; int /*<<< orphan*/ * tail; struct netconfig_vars* head; } ;

/* Variables and functions */
 scalar_t__ NC_INVALID ; 
 int /*<<< orphan*/  NC_NOTINIT ; 
 scalar_t__ NC_STORAGE ; 
 scalar_t__ NC_VALID ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct netconfig_vars*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nc_error ; 
 int /*<<< orphan*/ * nc_file ; 
 int /*<<< orphan*/  nc_file_lock ; 
 TYPE_1__ ni ; 
 int /*<<< orphan*/  ni_lock ; 

int
endnetconfig(void *handlep)
{
    struct netconfig_vars *nc_handlep = (struct netconfig_vars *)handlep;

    struct netconfig_list *q, *p;

    /*
     * Verify that handle is valid
     */
    if (nc_handlep == NULL || (nc_handlep->valid != NC_VALID &&
	    nc_handlep->valid != NC_STORAGE)) {
	nc_error = NC_NOTINIT;
	return (-1);
    }

    /*
     * Return 0 if anyone still needs it.
     */
    nc_handlep->valid = NC_INVALID;
    nc_handlep->flag = 0;
    nc_handlep->nc_configs = NULL;
    mutex_lock(&ni_lock);
    if (--ni.ref > 0) {
	mutex_unlock(&ni_lock);
    	free(nc_handlep);
	return(0);
    }

    /*
     * No one needs these entries anymore, then frees them.
     * Make sure all info in netconfig_info structure has been reinitialized.
     */
    q = ni.head;
    ni.eof = ni.ref = 0;
    ni.head = NULL;
    ni.tail = NULL;
    mutex_unlock(&ni_lock);

    while (q != NULL) {
	p = q->next;
	free(q->ncp->nc_lookups);
	free(q->ncp);
	free(q->linep);
	free(q);
	q = p;
    }
    free(nc_handlep);

    mutex_lock(&nc_file_lock);
    fclose(nc_file);
    nc_file = NULL;
    mutex_unlock(&nc_file_lock);

    return (0);
}