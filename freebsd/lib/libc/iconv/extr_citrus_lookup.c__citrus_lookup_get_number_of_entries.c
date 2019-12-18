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
struct _citrus_lookup {int (* cl_num_entries ) (struct _citrus_lookup*) ;} ;

/* Variables and functions */
 int stub1 (struct _citrus_lookup*) ; 

int
_citrus_lookup_get_number_of_entries(struct _citrus_lookup *cl)
{

	return ((*cl->cl_num_entries)(cl));
}