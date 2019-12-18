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

/* Variables and functions */

__attribute__((used)) static int
bhnd_nvram_bcmraw_getvar_order(struct bhnd_nvram_data *nv, void *cookiep1,
    void *cookiep2)
{
	if (cookiep1 < cookiep2)
		return (-1);

	if (cookiep1 > cookiep2)
		return (1);

	return (0);
}