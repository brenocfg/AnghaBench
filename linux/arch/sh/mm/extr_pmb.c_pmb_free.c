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
struct pmb_entry {int /*<<< orphan*/ * link; int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMB_NO_ENTRY ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmb_map ; 

__attribute__((used)) static void pmb_free(struct pmb_entry *pmbe)
{
	__clear_bit(pmbe->entry, pmb_map);

	pmbe->entry	= PMB_NO_ENTRY;
	pmbe->link	= NULL;
}