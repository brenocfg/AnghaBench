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
struct gmesh {int dummy; } ;
struct ggeom {TYPE_1__* lg_class; } ;
struct TYPE_2__ {char* lg_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  errc (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*) ; 
 struct ggeom* find_geom_by_provider (struct gmesh*,char const*) ; 
 int geom_gettree (struct gmesh*) ; 
 int /*<<< orphan*/  list_one_geom (struct ggeom*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
list_one_geom_by_provider(const char *provider_name)
{
	struct gmesh mesh;
	struct ggeom *gp;
	int error;

	error = geom_gettree(&mesh);
	if (error != 0)
		errc(EXIT_FAILURE, error, "Cannot get GEOM tree");

	gp = find_geom_by_provider(&mesh, provider_name);
	if (gp == NULL)
		errx(EXIT_FAILURE, "Cannot find provider '%s'.", provider_name);

	printf("Geom class: %s\n", gp->lg_class->lg_name);
	list_one_geom(gp);
}