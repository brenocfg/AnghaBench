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
struct lockf_entry {scalar_t__ lf_start; scalar_t__ lf_end; } ;

/* Variables and functions */

__attribute__((used)) static int
lf_overlaps(struct lockf_entry *x, struct lockf_entry *y)
{

	return (x->lf_start <= y->lf_end && x->lf_end >= y->lf_start);
}