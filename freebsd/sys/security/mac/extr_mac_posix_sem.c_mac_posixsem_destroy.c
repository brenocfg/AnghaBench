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
struct ksem {int /*<<< orphan*/ * ks_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  mac_posixsem_label_free (int /*<<< orphan*/ *) ; 

void
mac_posixsem_destroy(struct ksem *ks)
{

	if (ks->ks_label != NULL) {
		mac_posixsem_label_free(ks->ks_label);
		ks->ks_label = NULL;
	}
}