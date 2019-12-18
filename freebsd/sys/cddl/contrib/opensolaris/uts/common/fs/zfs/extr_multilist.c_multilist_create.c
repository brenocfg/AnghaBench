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
typedef  int /*<<< orphan*/  multilist_t ;
typedef  int /*<<< orphan*/  multilist_sublist_index_func_t ;

/* Variables and functions */
 int MAX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  max_ncpus ; 
 int /*<<< orphan*/ * multilist_create_impl (size_t,size_t,int,int /*<<< orphan*/ *) ; 
 int zfs_multilist_num_sublists ; 

multilist_t *
multilist_create(size_t size, size_t offset,
    multilist_sublist_index_func_t *index_func)
{
	int num_sublists;

	if (zfs_multilist_num_sublists > 0) {
		num_sublists = zfs_multilist_num_sublists;
	} else {
		num_sublists = MAX(max_ncpus, 4);
	}

	return (multilist_create_impl(size, offset, num_sublists, index_func));
}