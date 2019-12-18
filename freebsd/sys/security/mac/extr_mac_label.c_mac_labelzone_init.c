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
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int /*<<< orphan*/  mac_labelzone_ctor ; 
 int /*<<< orphan*/  mac_labelzone_dtor ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_label ; 

void
mac_labelzone_init(void)
{

	zone_label = uma_zcreate("MAC labels", sizeof(struct label),
	    mac_labelzone_ctor, mac_labelzone_dtor, NULL, NULL,
	    UMA_ALIGN_PTR, 0);
}