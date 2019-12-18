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
typedef  int /*<<< orphan*/  ofw_t ;

/* Variables and functions */
 int fdt_check_header (void*) ; 
 void* fdtp ; 

__attribute__((used)) static int
ofw_fdt_init(ofw_t ofw, void *data)
{
	int err;

	/* Check FDT blob integrity */
	if ((err = fdt_check_header(data)) != 0)
		return (err);

	fdtp = data;
	return (0);
}