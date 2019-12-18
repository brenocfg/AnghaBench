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
struct gprovider {int dummy; } ;
struct gmesh {int dummy; } ;

/* Variables and functions */
 struct gprovider* find_provider_by_name (struct gmesh*,char const*) ; 
 char* geom_pp_attr (struct gmesh*,struct gprovider*,char*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static char *
find_geom_efimedia(struct gmesh *mesh, const char *dev)
{
	struct gprovider *pp;
	const char *efimedia;

	pp = find_provider_by_name(mesh, dev);
	if (pp == NULL)
		return (NULL);
	efimedia = geom_pp_attr(mesh, pp, "efimedia");
	if (efimedia == NULL)
		return (NULL);
	return strdup(efimedia);
}