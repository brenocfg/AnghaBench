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
struct env_var {int (* ev_sethook ) (struct env_var*,int,void const*) ;char* ev_value; int ev_flags; struct env_var* ev_prev; struct env_var* ev_next; void* ev_name; int /*<<< orphan*/  ev_unsethook; } ;
typedef  int /*<<< orphan*/  ev_unsethook_t ;
typedef  int (* ev_sethook_t ) (struct env_var*,int,void const*) ;

/* Variables and functions */
 int EV_DYNAMIC ; 
 int EV_NOHOOK ; 
 int EV_VOLATILE ; 
 struct env_var* env_getenv (char const*) ; 
 struct env_var* environ ; 
 int /*<<< orphan*/  free (char*) ; 
 struct env_var* malloc (int) ; 
 scalar_t__ strcmp (void*,void*) ; 
 void* strdup (void const*) ; 
 int stub1 (struct env_var*,int,void const*) ; 

int
env_setenv(const char *name, int flags, const void *value,
	   ev_sethook_t sethook, ev_unsethook_t unsethook)
{
    struct env_var	*ev, *curr, *last;

    if ((ev = env_getenv(name)) != NULL) {
	/*
	 * If there's a set hook, let it do the work (unless we are working
	 * for one already.
	 */
	if ((ev->ev_sethook != NULL) && !(flags & EV_NOHOOK))
	    return (ev->ev_sethook(ev, flags, value));

	/* If there is data in the variable, discard it. */
	if (ev->ev_value != NULL && (ev->ev_flags & EV_DYNAMIC) != 0)
	    free(ev->ev_value);
	ev->ev_value = NULL;
	ev->ev_flags &= ~EV_DYNAMIC;

    } else {

	/*
	 * New variable; create and sort into list
	 */
	ev = malloc(sizeof(struct env_var));
	ev->ev_name = strdup(name);
	ev->ev_value = NULL;
	ev->ev_flags = 0;
	/* hooks can only be set when the variable is instantiated */
	ev->ev_sethook = sethook;
	ev->ev_unsethook = unsethook;

	/* Sort into list */
	ev->ev_prev = NULL;
	ev->ev_next = NULL;
	/* Search for the record to insert before */
	for (last = NULL, curr = environ; 
	     curr != NULL; 
	     last = curr, curr = curr->ev_next) {

	    if (strcmp(ev->ev_name, curr->ev_name) < 0) {
		if (curr->ev_prev) {
		    curr->ev_prev->ev_next = ev;
		} else {
		    environ = ev;
		}
		ev->ev_next = curr;
		ev->ev_prev = curr->ev_prev;
		curr->ev_prev = ev;
		break;
	    }
	}
	if (curr == NULL) {
	    if (last == NULL) {
		environ = ev;
	    } else {
		last->ev_next = ev;
		ev->ev_prev = last;
	    }
	}
    }

    /* If we have a new value, use it */
    if (flags & EV_VOLATILE) {
	ev->ev_value = strdup(value);
	ev->ev_flags |= EV_DYNAMIC;
    } else {
	ev->ev_value = (char *)value;
	ev->ev_flags |= flags & EV_DYNAMIC;
    }

    return(0);
}