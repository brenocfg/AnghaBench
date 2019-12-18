#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bhnd_nvram_sprom {TYPE_1__* layout; } ;
struct bhnd_nvram_data {int dummy; } ;
struct TYPE_2__ {size_t num_vars; } ;

/* Variables and functions */

size_t
bhnd_nvram_sprom_count(struct bhnd_nvram_data *nv)
{
	struct bhnd_nvram_sprom *sprom = (struct bhnd_nvram_sprom *)nv;
	return (sprom->layout->num_vars);
}