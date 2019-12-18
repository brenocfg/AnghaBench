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
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct label*) ; 
 int /*<<< orphan*/  zone_label ; 

void
mac_labelzone_free(struct label *label)
{

	uma_zfree(zone_label, label);
}