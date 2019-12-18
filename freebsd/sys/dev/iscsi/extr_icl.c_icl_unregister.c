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
struct icl_module {struct icl_module* im_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_modules; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  ICL_DEBUG (char*,char const*) ; 
 int /*<<< orphan*/  ICL_WARN (char*,char const*) ; 
 int /*<<< orphan*/  M_ICL ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct icl_module*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct icl_module*,int /*<<< orphan*/ ) ; 
 struct icl_module* icl_find (char const*,int,int) ; 
 int /*<<< orphan*/  im_next ; 
 TYPE_1__* sc ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
icl_unregister(const char *offload, bool rdma)
{
	struct icl_module *im;

	sx_xlock(&sc->sc_lock);
	im = icl_find(offload, rdma, true);
	if (im == NULL) {
		ICL_WARN("offload \"%s\" not registered", offload);
		sx_xunlock(&sc->sc_lock);
		return (ENXIO);
	}

	TAILQ_REMOVE(&sc->sc_modules, im, im_next);
	sx_xunlock(&sc->sc_lock);

	free(im->im_name, M_ICL);
	free(im, M_ICL);

	ICL_DEBUG("offload \"%s\" unregistered", offload);
	return (0);
}