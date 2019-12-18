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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int grant_ref_t ;

/* Variables and functions */
 scalar_t__ __predict_false (int) ; 
 int get_free_entries (int /*<<< orphan*/ ,int*) ; 

int
gnttab_alloc_grant_references(uint16_t count, grant_ref_t *head)
{
	int ref, error;

	error = get_free_entries(count, &ref);
	if (__predict_false(error))
		return (error);

	*head = ref;
	return (0);
}