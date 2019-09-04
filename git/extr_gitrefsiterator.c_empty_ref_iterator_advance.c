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
struct ref_iterator {int dummy; } ;

/* Variables and functions */
 int ref_iterator_abort (struct ref_iterator*) ; 

__attribute__((used)) static int empty_ref_iterator_advance(struct ref_iterator *ref_iterator)
{
	return ref_iterator_abort(ref_iterator);
}