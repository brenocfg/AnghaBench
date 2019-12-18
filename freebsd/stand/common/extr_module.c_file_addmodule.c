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
struct preloaded_file {struct kernel_module* f_modules; } ;
struct mod_depend {int md_ver_preferred; } ;
struct kernel_module {int m_version; struct kernel_module* m_next; struct preloaded_file* m_fp; int /*<<< orphan*/ * m_name; } ;
typedef  int /*<<< orphan*/  mdepend ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  bzero (struct mod_depend*,int) ; 
 struct kernel_module* calloc (int,int) ; 
 struct kernel_module* file_findmodule (struct preloaded_file*,char*,struct mod_depend*) ; 
 int /*<<< orphan*/  free (struct kernel_module*) ; 
 int /*<<< orphan*/ * strdup (char*) ; 

int
file_addmodule(struct preloaded_file *fp, char *modname, int version,
	struct kernel_module **newmp)
{
	struct kernel_module *mp;
	struct mod_depend mdepend;

	bzero(&mdepend, sizeof(mdepend));
	mdepend.md_ver_preferred = version;
	mp = file_findmodule(fp, modname, &mdepend);
	if (mp)
		return (EEXIST);
	mp = calloc(1, sizeof(struct kernel_module));
	if (mp == NULL)
		return (ENOMEM);
	mp->m_name = strdup(modname);
	if (mp->m_name == NULL) {
		free(mp);
		return (ENOMEM);
	}
	mp->m_version = version;
	mp->m_fp = fp;
	mp->m_next = fp->f_modules;
	fp->f_modules = mp;
	if (newmp)
		*newmp = mp;
	return (0);
}