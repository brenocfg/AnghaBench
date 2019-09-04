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
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 

__attribute__((used)) static int files_reflog_iterator_peel(struct ref_iterator *ref_iterator,
				   struct object_id *peeled)
{
	BUG("ref_iterator_peel() called for reflog_iterator");
}