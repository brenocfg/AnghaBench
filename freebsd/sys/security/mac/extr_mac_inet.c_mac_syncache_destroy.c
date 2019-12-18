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
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_POLICY_PERFORM_NOSLEEP (int /*<<< orphan*/ ,struct label*) ; 
 int /*<<< orphan*/  mac_labelzone_free (struct label*) ; 
 int /*<<< orphan*/  syncache_destroy_label ; 

void
mac_syncache_destroy(struct label **label)
{

	if (*label != NULL) {
		MAC_POLICY_PERFORM_NOSLEEP(syncache_destroy_label, *label);
		mac_labelzone_free(*label);
		*label = NULL;
	}
}