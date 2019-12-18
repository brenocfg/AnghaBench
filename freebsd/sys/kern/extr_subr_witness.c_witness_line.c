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
struct witness {int w_line; } ;
struct lock_object {struct witness* lo_witness; } ;

/* Variables and functions */
 scalar_t__ witness_cold ; 
 int witness_watch ; 

int
witness_line(struct lock_object *lock)
{
	struct witness *w;

	if (witness_cold || witness_watch < 1 || lock->lo_witness == NULL)
		return (0);
	w = lock->lo_witness;
	return (w->w_line);
}