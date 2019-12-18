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
struct TYPE_3__ {int /*<<< orphan*/  data_type; } ;
typedef  TYPE_1__ bhnd_nvram_val ;
typedef  int /*<<< orphan*/  bhnd_nvram_type ;

/* Variables and functions */
 int /*<<< orphan*/  bhnd_nvram_base_type (int /*<<< orphan*/ ) ; 

bhnd_nvram_type
bhnd_nvram_val_elem_type(bhnd_nvram_val *value)
{
	return (bhnd_nvram_base_type(value->data_type));
}