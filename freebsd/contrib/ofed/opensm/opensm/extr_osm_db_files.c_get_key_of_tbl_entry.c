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
typedef  scalar_t__ st_data_t ;
typedef  int /*<<< orphan*/  cl_list_t ;

/* Variables and functions */
 int ST_CONTINUE ; 
 int /*<<< orphan*/  cl_list_insert_tail (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int get_key_of_tbl_entry(st_data_t key, st_data_t val, st_data_t arg)
{
	cl_list_t *p_list = (cl_list_t *) arg;
	cl_list_insert_tail(p_list, (void *)key);
	return ST_CONTINUE;
}