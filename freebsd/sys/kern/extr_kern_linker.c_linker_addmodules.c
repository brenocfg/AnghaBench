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
struct mod_version {int mv_version; } ;
struct mod_metadata {scalar_t__ md_type; char* md_cval; scalar_t__ md_data; } ;
typedef  int /*<<< orphan*/  linker_file_t ;

/* Variables and functions */
 scalar_t__ MDT_VERSION ; 
 int /*<<< orphan*/ * modlist_lookup (char const*,int) ; 
 int /*<<< orphan*/  modlist_newmodule (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static void
linker_addmodules(linker_file_t lf, struct mod_metadata **start,
    struct mod_metadata **stop, int preload)
{
	struct mod_metadata *mp, **mdp;
	const char *modname;
	int ver;

	for (mdp = start; mdp < stop; mdp++) {
		mp = *mdp;
		if (mp->md_type != MDT_VERSION)
			continue;
		modname = mp->md_cval;
		ver = ((const struct mod_version *)mp->md_data)->mv_version;
		if (modlist_lookup(modname, ver) != NULL) {
			printf("module %s already present!\n", modname);
			/* XXX what can we do? this is a build error. :-( */
			continue;
		}
		modlist_newmodule(modname, ver, lf);
	}
}