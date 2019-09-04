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
typedef  int /*<<< orphan*/  JSON_Malloc_Function ;
typedef  int /*<<< orphan*/  JSON_Free_Function ;

/* Variables and functions */
 int /*<<< orphan*/  parson_free ; 
 int /*<<< orphan*/  parson_malloc ; 

void json_set_allocation_functions(JSON_Malloc_Function malloc_fun, JSON_Free_Function free_fun) {
    parson_malloc = malloc_fun;
    parson_free = free_fun;
}