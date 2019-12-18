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
struct bhnd_nvram_data {int dummy; } ;
typedef  int /*<<< orphan*/  bhnd_nvram_val ;

/* Variables and functions */
 int bhnd_nvram_data_generic_rp_copy_val (struct bhnd_nvram_data*,void*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
bhnd_nvram_btxt_copy_val(struct bhnd_nvram_data *nv, void *cookiep,
    bhnd_nvram_val **value)
{
	return (bhnd_nvram_data_generic_rp_copy_val(nv, cookiep, value));
}