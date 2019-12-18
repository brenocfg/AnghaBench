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

/* Variables and functions */
 int FDT_ERR_NOTFOUND ; 
 int /*<<< orphan*/  debugf (char*,char const*) ; 
 int fdt_load_dtb_overlay (char*) ; 
 int /*<<< orphan*/  fdt_print_overlay_load_error (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
fdt_load_dtb_overlays_string(const char * filenames)
{
	char *names;
	char *name, *name_ext;
	char *comaptr;
	int err, namesz;

	debugf("fdt_load_dtb_overlays_string(%s)\n", filenames);

	names = strdup(filenames);
	if (names == NULL)
		return (1);
	name = names;
	do {
		comaptr = strchr(name, ',');
		if (comaptr)
			*comaptr = '\0';
		err = fdt_load_dtb_overlay(name);
		if (err == FDT_ERR_NOTFOUND) {
			/* Allocate enough to append ".dtbo" */
			namesz = strlen(name) + 6;
			name_ext = malloc(namesz);
			if (name_ext == NULL) {
				fdt_print_overlay_load_error(err, name);
				name = comaptr + 1;
				continue;
			}
			snprintf(name_ext, namesz, "%s.dtbo", name);
			err = fdt_load_dtb_overlay(name_ext);
			free(name_ext);
		}
		/* Catch error with either initial load or fallback load */
		if (err != 0)
			fdt_print_overlay_load_error(err, name);
		name = comaptr + 1;
	} while(comaptr);

	free(names);
	return (0);
}