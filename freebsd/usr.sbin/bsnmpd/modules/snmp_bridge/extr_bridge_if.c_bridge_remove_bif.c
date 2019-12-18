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
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct bridge_if*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b_if ; 
 int /*<<< orphan*/  bridge_addrs_free (struct bridge_if*) ; 
 int /*<<< orphan*/  bridge_ifs ; 
 int /*<<< orphan*/  bridge_members_free (struct bridge_if*) ; 
 int /*<<< orphan*/  free (struct bridge_if*) ; 

void
bridge_remove_bif(struct bridge_if *bif)
{
	bridge_members_free(bif);
	bridge_addrs_free(bif);
	TAILQ_REMOVE(&bridge_ifs, bif, b_if);
	free(bif);
}