#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bhnd_nvram_val ;
struct TYPE_3__ {int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ bhnd_nvram_prop ;

/* Variables and functions */

bhnd_nvram_val *
bhnd_nvram_prop_val(bhnd_nvram_prop *prop)
{
	return (prop->val);
}