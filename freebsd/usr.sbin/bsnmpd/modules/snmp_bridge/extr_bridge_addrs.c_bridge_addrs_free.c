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
struct bridge_if {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bridge_tpe_bif_free (int /*<<< orphan*/ *,struct bridge_if*) ; 
 int /*<<< orphan*/  tp_entries ; 

void
bridge_addrs_free(struct bridge_if *bif)
{
	bridge_tpe_bif_free(&tp_entries, bif);
}