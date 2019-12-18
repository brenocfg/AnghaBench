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
struct dbm_match {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITER_SECT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_bytitle (int /*<<< orphan*/ ,struct dbm_match const*) ; 

void
dbm_page_bysect(const struct dbm_match *match)
{
	assert(match != NULL);
	page_bytitle(ITER_SECT, match);
}