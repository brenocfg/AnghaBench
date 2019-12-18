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

/* Variables and functions */
 char* boot_disk (struct gmesh*) ; 
 int /*<<< orphan*/  dlg_clear () ; 
 int /*<<< orphan*/  dlg_put_backtitle () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  geom_deletetree (struct gmesh*) ; 
 int geom_gettree (struct gmesh*) ; 
 int wizard_makeparts (struct gmesh*,char*,char const*,int) ; 
 char* wizard_partition (struct gmesh*,char*) ; 

int
part_wizard(const char *fsreq)
{
	char *disk, *schemeroot;
	const char *fstype;
	struct gmesh mesh;
	int error;

	if (fsreq != NULL)
		fstype = fsreq;
	else
		fstype = "ufs";

startwizard:
	error = geom_gettree(&mesh);

	dlg_put_backtitle();
	error = geom_gettree(&mesh);
	disk = boot_disk(&mesh);
	if (disk == NULL)
		return (1);

	dlg_clear();
	dlg_put_backtitle();
	schemeroot = wizard_partition(&mesh, disk);
	free(disk);
	if (schemeroot == NULL)
		return (1);

	geom_deletetree(&mesh);
	dlg_clear();
	dlg_put_backtitle();
	error = geom_gettree(&mesh);

	error = wizard_makeparts(&mesh, schemeroot, fstype, 1);
	if (error)
		goto startwizard;
	free(schemeroot);

	geom_deletetree(&mesh);

	return (0);
}