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
struct gmesh {int dummy; } ;
struct gclass {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  errc (int /*<<< orphan*/ ,int,char*) ; 
 struct gclass* find_class (struct gmesh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gclass_name ; 
 int /*<<< orphan*/  geom_deletetree (struct gmesh*) ; 
 int geom_gettree (struct gmesh*) ; 

__attribute__((used)) static int
std_list_available(void)
{
	struct gmesh mesh;
	struct gclass *classp;
	int error;

	error = geom_gettree(&mesh);
	if (error != 0)
		errc(EXIT_FAILURE, error, "Cannot get GEOM tree");
	classp = find_class(&mesh, gclass_name);
	geom_deletetree(&mesh);
	if (classp != NULL)
		return (1);
	return (0);
}