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
struct preloaded_file {struct kernel_module* f_modules; struct preloaded_file* f_next; } ;
struct mod_depend {int md_ver_preferred; int md_ver_minimum; int md_ver_maximum; } ;
struct kernel_module {int m_version; int /*<<< orphan*/  m_name; struct kernel_module* m_next; } ;

/* Variables and functions */
 struct preloaded_file* preloaded_files ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

struct kernel_module *
file_findmodule(struct preloaded_file *fp, char *modname,
	struct mod_depend *verinfo)
{
	struct kernel_module *mp, *best;
	int bestver, mver;

	if (fp == NULL) {
		for (fp = preloaded_files; fp; fp = fp->f_next) {
			mp = file_findmodule(fp, modname, verinfo);
			if (mp)
				return (mp);
		}
		return (NULL);
	}
	best = NULL;
	bestver = 0;
	for (mp = fp->f_modules; mp; mp = mp->m_next) {
		if (strcmp(modname, mp->m_name) == 0) {
			if (verinfo == NULL)
				return (mp);
			mver = mp->m_version;
			if (mver == verinfo->md_ver_preferred)
				return (mp);
			if (mver >= verinfo->md_ver_minimum &&
			  mver <= verinfo->md_ver_maximum &&
			  mver > bestver) {
				best = mp;
				bestver = mver;
			}
		}
	}
	return (best);
}