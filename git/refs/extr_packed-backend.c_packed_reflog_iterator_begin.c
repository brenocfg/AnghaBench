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
struct ref_store {int dummy; } ;
struct ref_iterator {int dummy; } ;

/* Variables and functions */
 struct ref_iterator* empty_ref_iterator_begin () ; 

__attribute__((used)) static struct ref_iterator *packed_reflog_iterator_begin(struct ref_store *ref_store)
{
	return empty_ref_iterator_begin();
}