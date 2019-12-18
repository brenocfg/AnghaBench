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
struct gprovider {struct gprovider* lg_mode; int /*<<< orphan*/  lg_config; int /*<<< orphan*/  lg_consumer; struct gprovider* lg_name; int /*<<< orphan*/  lg_provider; int /*<<< orphan*/  lg_geom; } ;
struct gmesh {int /*<<< orphan*/  lg_class; struct gprovider* lg_ident; } ;
struct ggeom {struct ggeom* lg_mode; int /*<<< orphan*/  lg_config; int /*<<< orphan*/  lg_consumer; struct ggeom* lg_name; int /*<<< orphan*/  lg_provider; int /*<<< orphan*/  lg_geom; } ;
struct gconsumer {struct gconsumer* lg_mode; int /*<<< orphan*/  lg_config; int /*<<< orphan*/  lg_consumer; struct gconsumer* lg_name; int /*<<< orphan*/  lg_provider; int /*<<< orphan*/  lg_geom; } ;
struct gclass {struct gclass* lg_mode; int /*<<< orphan*/  lg_config; int /*<<< orphan*/  lg_consumer; struct gclass* lg_name; int /*<<< orphan*/  lg_provider; int /*<<< orphan*/  lg_geom; } ;

/* Variables and functions */
 struct gprovider* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct gprovider*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_config (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct gprovider*) ; 
 int /*<<< orphan*/  lg_class ; 
 int /*<<< orphan*/  lg_consumer ; 
 int /*<<< orphan*/  lg_geom ; 
 int /*<<< orphan*/  lg_provider ; 

void
geom_deletetree(struct gmesh *gmp)
{
	struct gclass *cl;
	struct ggeom *ge;
	struct gprovider *pr;
	struct gconsumer *co;

	free(gmp->lg_ident);
	gmp->lg_ident = NULL;
	for (;;) {
		cl = LIST_FIRST(&gmp->lg_class);
		if (cl == NULL) 
			break;
		LIST_REMOVE(cl, lg_class);
		delete_config(&cl->lg_config);
		if (cl->lg_name) free(cl->lg_name);
		for (;;) {
			ge = LIST_FIRST(&cl->lg_geom);
			if (ge == NULL) 
				break;
			LIST_REMOVE(ge, lg_geom);
			delete_config(&ge->lg_config);
			if (ge->lg_name) free(ge->lg_name);
			for (;;) {
				pr = LIST_FIRST(&ge->lg_provider);
				if (pr == NULL) 
					break;
				LIST_REMOVE(pr, lg_provider);
				delete_config(&pr->lg_config);
				if (pr->lg_name) free(pr->lg_name);
				if (pr->lg_mode) free(pr->lg_mode);
				free(pr);
			}
			for (;;) {
				co = LIST_FIRST(&ge->lg_consumer);
				if (co == NULL) 
					break;
				LIST_REMOVE(co, lg_consumer);
				delete_config(&co->lg_config);
				if (co->lg_mode) free(co->lg_mode);
				free(co);
			}
			free(ge);
		}
		free(cl);
	}
}