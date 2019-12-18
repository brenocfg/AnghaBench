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
struct mod_item {int /*<<< orphan*/ * main_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IPFW ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ta_flush_mod_numarray(void *ta_buf)
{
	struct mod_item *mi;

	mi = (struct mod_item *)ta_buf;
	if (mi->main_ptr != NULL)
		free(mi->main_ptr, M_IPFW);
}