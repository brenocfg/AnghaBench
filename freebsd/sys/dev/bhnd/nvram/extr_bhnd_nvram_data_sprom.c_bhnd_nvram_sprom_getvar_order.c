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
struct bhnd_sprom_opcode_idx_entry {int dummy; } ;
struct bhnd_nvram_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
bhnd_nvram_sprom_getvar_order(struct bhnd_nvram_data *nv, void *cookiep1,
    void *cookiep2)
{
	struct bhnd_sprom_opcode_idx_entry *e1, *e2;

	e1 = cookiep1;
	e2 = cookiep2;

	/* Use the index entry order; this matches the order of variables
	 * returned via bhnd_nvram_sprom_next() */
	if (e1 < e2)
		return (-1);
	else if (e1 > e2)
		return (1);

	return (0);
}