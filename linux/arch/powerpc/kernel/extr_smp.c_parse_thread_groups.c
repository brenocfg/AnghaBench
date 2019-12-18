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
typedef  void* u32 ;
struct thread_groups {unsigned int property; int nr_groups; int threads_per_group; void** thread_list; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  MAX_THREAD_LIST_SIZE ; 
 int of_property_read_u32_array (struct device_node*,char*,void**,int) ; 

__attribute__((used)) static int parse_thread_groups(struct device_node *dn,
			       struct thread_groups *tg,
			       unsigned int property)
{
	int i;
	u32 thread_group_array[3 + MAX_THREAD_LIST_SIZE];
	u32 *thread_list;
	size_t total_threads;
	int ret;

	ret = of_property_read_u32_array(dn, "ibm,thread-groups",
					 thread_group_array, 3);
	if (ret)
		return ret;

	tg->property = thread_group_array[0];
	tg->nr_groups = thread_group_array[1];
	tg->threads_per_group = thread_group_array[2];
	if (tg->property != property ||
	    tg->nr_groups < 1 ||
	    tg->threads_per_group < 1)
		return -ENODATA;

	total_threads = tg->nr_groups * tg->threads_per_group;

	ret = of_property_read_u32_array(dn, "ibm,thread-groups",
					 thread_group_array,
					 3 + total_threads);
	if (ret)
		return ret;

	thread_list = &thread_group_array[3];

	for (i = 0 ; i < total_threads; i++)
		tg->thread_list[i] = thread_list[i];

	return 0;
}