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
struct lockf_entry {scalar_t__ lf_owner; scalar_t__ lf_type; } ;

/* Variables and functions */
 scalar_t__ F_WRLCK ; 
 scalar_t__ lf_overlaps (struct lockf_entry*,struct lockf_entry*) ; 

__attribute__((used)) static int
lf_blocks(struct lockf_entry *x, struct lockf_entry *y)
{

	return x->lf_owner != y->lf_owner
		&& (x->lf_type == F_WRLCK || y->lf_type == F_WRLCK)
		&& lf_overlaps(x, y);
}