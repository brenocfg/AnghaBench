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
typedef  int /*<<< orphan*/  f_internal_t ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  create_lid2guid (int /*<<< orphan*/ *) ; 

f_internal_t *allocate_fabric_internal(void)
{
	f_internal_t *f = calloc(1, sizeof(*f));
	if (f)
		create_lid2guid(f);

	return (f);
}