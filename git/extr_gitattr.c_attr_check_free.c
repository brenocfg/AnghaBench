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
struct attr_check {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  attr_check_clear (struct attr_check*) ; 
 int /*<<< orphan*/  check_vector_remove (struct attr_check*) ; 
 int /*<<< orphan*/  free (struct attr_check*) ; 

void attr_check_free(struct attr_check *check)
{
	if (check) {
		/* Remove check from the check vector */
		check_vector_remove(check);

		attr_check_clear(check);
		free(check);
	}
}