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
struct mtx {int dummy; } ;
struct icl_module {struct icl_conn* (* im_new_conn ) (char const*,struct mtx*) ;} ;
struct icl_conn {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc_lock; } ;

/* Variables and functions */
 struct icl_module* icl_find (char const*,int,int) ; 
 TYPE_1__* sc ; 
 struct icl_conn* stub1 (char const*,struct mtx*) ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 

struct icl_conn *
icl_new_conn(const char *offload, bool iser, const char *name, struct mtx *lock)
{
	struct icl_module *im;
	struct icl_conn *ic;

	sx_slock(&sc->sc_lock);
	im = icl_find(offload, iser, false);
	if (im == NULL) {
		sx_sunlock(&sc->sc_lock);
		return (NULL);
	}

	ic = im->im_new_conn(name, lock);
	sx_sunlock(&sc->sc_lock);

	return (ic);
}