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
struct filter_entry {int /*<<< orphan*/ * smt; int /*<<< orphan*/ * l2te; } ;

/* Variables and functions */
 int /*<<< orphan*/  t4_l2t_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_smt_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_filter_resources(struct filter_entry *f)
{

	if (f->l2te) {
		t4_l2t_release(f->l2te);
		f->l2te = NULL;
	}
	if (f->smt) {
		t4_smt_release(f->smt);
		f->smt = NULL;
	}
}