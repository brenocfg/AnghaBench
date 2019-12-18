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
struct seq_file {scalar_t__ private; } ;

/* Variables and functions */
 unsigned long EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_USER ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 unsigned long callback_getenv (unsigned long,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  seq_write (struct seq_file*,char*,unsigned long) ; 

__attribute__((used)) static int srm_env_proc_show(struct seq_file *m, void *v)
{
	unsigned long	ret;
	unsigned long	id = (unsigned long)m->private;
	char		*page;

	page = (char *)__get_free_page(GFP_USER);
	if (!page)
		return -ENOMEM;

	ret = callback_getenv(id, page, PAGE_SIZE);

	if ((ret >> 61) == 0) {
		seq_write(m, page, ret);
		ret = 0;
	} else
		ret = -EFAULT;
	free_page((unsigned long)page);
	return ret;
}