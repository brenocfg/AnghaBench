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
struct ldt_struct {int /*<<< orphan*/  nr_entries; int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  paravirt_alloc_ldt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void finalize_ldt_struct(struct ldt_struct *ldt)
{
	paravirt_alloc_ldt(ldt->entries, ldt->nr_entries);
}