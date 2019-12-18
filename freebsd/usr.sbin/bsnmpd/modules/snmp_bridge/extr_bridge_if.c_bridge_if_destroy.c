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
struct bridge_if {int /*<<< orphan*/  bif_name; } ;

/* Variables and functions */
 scalar_t__ bridge_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bridge_remove_bif (struct bridge_if*) ; 

__attribute__((used)) static int
bridge_if_destroy(struct bridge_if *bif)
{
	if (bridge_destroy(bif->bif_name) < 0)
		return (-1);

	bridge_remove_bif(bif);

	return (0);
}