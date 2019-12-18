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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct id_table {int match_flags; scalar_t__ lmp_subver; scalar_t__ hci_rev; scalar_t__ hci_ver; scalar_t__ hci_bus; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct id_table const*) ; 
 int IC_MATCH_FL_HCIBUS ; 
 int IC_MATCH_FL_HCIREV ; 
 int IC_MATCH_FL_HCIVER ; 
 int IC_MATCH_FL_LMPSUBV ; 
 struct id_table const* ic_id_table ; 

__attribute__((used)) static const struct id_table *btrtl_match_ic(u16 lmp_subver, u16 hci_rev,
					     u8 hci_ver, u8 hci_bus)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ic_id_table); i++) {
		if ((ic_id_table[i].match_flags & IC_MATCH_FL_LMPSUBV) &&
		    (ic_id_table[i].lmp_subver != lmp_subver))
			continue;
		if ((ic_id_table[i].match_flags & IC_MATCH_FL_HCIREV) &&
		    (ic_id_table[i].hci_rev != hci_rev))
			continue;
		if ((ic_id_table[i].match_flags & IC_MATCH_FL_HCIVER) &&
		    (ic_id_table[i].hci_ver != hci_ver))
			continue;
		if ((ic_id_table[i].match_flags & IC_MATCH_FL_HCIBUS) &&
		    (ic_id_table[i].hci_bus != hci_bus))
			continue;

		break;
	}
	if (i >= ARRAY_SIZE(ic_id_table))
		return NULL;

	return &ic_id_table[i];
}