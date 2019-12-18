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
struct bhnd_nvram_sprom {int /*<<< orphan*/  state; } ;
struct bhnd_nvram_data {int dummy; } ;
typedef  void bhnd_sprom_opcode_idx_entry ;

/* Variables and functions */
 void* bhnd_sprom_opcode_index_find (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void *
bhnd_nvram_sprom_find(struct bhnd_nvram_data *nv, const char *name)
{
	struct bhnd_nvram_sprom		*sp;
	bhnd_sprom_opcode_idx_entry	*entry;

	sp = (struct bhnd_nvram_sprom *)nv;

	entry = bhnd_sprom_opcode_index_find(&sp->state, name);
	return (entry);
}