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
struct kernel_module {struct kernel_module* m_next; } ;

/* Variables and functions */

__attribute__((used)) static int
num_modules(struct preloaded_file *kfp)
{
	struct kernel_module	*kmp;
	int			 mod_num = 0;

	for (kmp = kfp->f_modules; kmp != NULL; kmp = kmp->m_next)
		mod_num++;

	return (mod_num);
}