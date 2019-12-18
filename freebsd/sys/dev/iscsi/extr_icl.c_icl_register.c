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
struct icl_module {int im_iser; int im_priority; int (* im_limits ) (struct icl_drv_limits*) ;struct icl_conn* (* im_new_conn ) (char const*,struct mtx*) ;int /*<<< orphan*/  im_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_modules; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ICL_DEBUG (char*,char const*) ; 
 int /*<<< orphan*/  ICL_WARN (char*,char const*) ; 
 int /*<<< orphan*/  M_ICL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct icl_module*,int /*<<< orphan*/ ) ; 
 struct icl_module* icl_find (char const*,int,int) ; 
 int /*<<< orphan*/  im_next ; 
 struct icl_module* malloc (int,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* sc ; 
 int /*<<< orphan*/  strdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
icl_register(const char *offload, bool iser, int priority,
    int (*limits)(struct icl_drv_limits *),
    struct icl_conn *(*new_conn)(const char *, struct mtx *))
{
	struct icl_module *im;

	sx_xlock(&sc->sc_lock);
	im = icl_find(offload, iser, true);
	if (im != NULL) {
		ICL_WARN("offload \"%s\" already registered", offload);
		sx_xunlock(&sc->sc_lock);
		return (EBUSY);
	}

	im = malloc(sizeof(*im), M_ICL, M_ZERO | M_WAITOK);
	im->im_name = strdup(offload, M_ICL);
	im->im_iser = iser;
	im->im_priority = priority;
	im->im_limits = limits;
	im->im_new_conn = new_conn;

	TAILQ_INSERT_HEAD(&sc->sc_modules, im, im_next);
	sx_xunlock(&sc->sc_lock);

	ICL_DEBUG("offload \"%s\" registered", offload);
	return (0);
}