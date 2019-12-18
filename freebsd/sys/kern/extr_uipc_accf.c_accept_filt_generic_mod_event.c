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
struct accept_filter {int /*<<< orphan*/  accf_name; } ;
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  MOD_LOAD 130 
#define  MOD_SHUTDOWN 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  M_ACCF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int accept_filt_add (struct accept_filter*) ; 
 int accept_filt_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct accept_filter*,struct accept_filter*,int) ; 
 struct accept_filter* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unloadable ; 

int
accept_filt_generic_mod_event(module_t mod, int event, void *data)
{
	struct accept_filter *p;
	struct accept_filter *accfp = (struct accept_filter *) data;
	int error;

	switch (event) {
	case MOD_LOAD:
		p = malloc(sizeof(*p), M_ACCF, M_WAITOK);
		bcopy(accfp, p, sizeof(*p));
		error = accept_filt_add(p);
		break;

	case MOD_UNLOAD:
		/*
		 * Do not support unloading yet. we don't keep track of
		 * refcounts and unloading an accept filter callback and then
		 * having it called is a bad thing.  A simple fix would be to
		 * track the refcount in the struct accept_filter.
		 */
		if (unloadable != 0) {
			error = accept_filt_del(accfp->accf_name);
		} else
			error = EOPNOTSUPP;
		break;

	case MOD_SHUTDOWN:
		error = 0;
		break;

	default:
		error = EOPNOTSUPP;
		break;
	}

	return (error);
}