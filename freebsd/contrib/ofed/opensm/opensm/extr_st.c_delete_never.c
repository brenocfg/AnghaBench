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

/* Variables and functions */
 int ST_CONTINUE ; 
 int ST_DELETE ; 

__attribute__((used)) static int delete_never(st_data_t key, st_data_t value, st_data_t never)
{
	if (value == never)
		return ST_DELETE;
	return ST_CONTINUE;
}