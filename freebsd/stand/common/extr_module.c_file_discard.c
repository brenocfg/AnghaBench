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
struct preloaded_file {struct preloaded_file* f_args; struct preloaded_file* f_type; struct preloaded_file* f_name; struct preloaded_file* m_next; struct preloaded_file* m_name; struct preloaded_file* f_modules; struct preloaded_file* md_next; struct preloaded_file* f_metadata; } ;
struct kernel_module {struct kernel_module* f_args; struct kernel_module* f_type; struct kernel_module* f_name; struct kernel_module* m_next; struct kernel_module* m_name; struct kernel_module* f_modules; struct kernel_module* md_next; struct kernel_module* f_metadata; } ;
struct file_metadata {struct file_metadata* f_args; struct file_metadata* f_type; struct file_metadata* f_name; struct file_metadata* m_next; struct file_metadata* m_name; struct file_metadata* f_modules; struct file_metadata* md_next; struct file_metadata* f_metadata; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct preloaded_file*) ; 

void
file_discard(struct preloaded_file *fp)
{
	struct file_metadata	*md, *md1;
	struct kernel_module	*mp, *mp1;
	if (fp == NULL)
		return;
	md = fp->f_metadata;
	while (md) {
		md1 = md;
		md = md->md_next;
		free(md1);
	}
	mp = fp->f_modules;
	while (mp) {
		free(mp->m_name);
		mp1 = mp;
		mp = mp->m_next;
		free(mp1);
	}
	free(fp->f_name);
	free(fp->f_type);
	free(fp->f_args);
	free(fp);
}