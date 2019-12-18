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
typedef  scalar_t__ uint32_t ;
struct cpsw_softc {int dummy; } ;

/* Variables and functions */
 int ALE_MCAST (scalar_t__*) ; 
 scalar_t__ ALE_TYPE (scalar_t__*) ; 
 scalar_t__ ALE_TYPE_ADDR ; 
 scalar_t__ ALE_TYPE_VLAN_ADDR ; 
 int CPSW_MAX_ALE_ENTRIES ; 
 int /*<<< orphan*/  cpsw_ale_read_entry (struct cpsw_softc*,int,scalar_t__*) ; 
 int /*<<< orphan*/  cpsw_ale_write_entry (struct cpsw_softc*,int,scalar_t__*) ; 

__attribute__((used)) static void
cpsw_ale_remove_all_mc_entries(struct cpsw_softc *sc)
{
	int i;
	uint32_t ale_entry[3];

	/* First four entries are link address and broadcast. */
	for (i = 10; i < CPSW_MAX_ALE_ENTRIES; i++) {
		cpsw_ale_read_entry(sc, i, ale_entry);
		if ((ALE_TYPE(ale_entry) == ALE_TYPE_ADDR ||
		    ALE_TYPE(ale_entry) == ALE_TYPE_VLAN_ADDR) &&
		    ALE_MCAST(ale_entry)  == 1) { /* MCast link addr */
			ale_entry[0] = ale_entry[1] = ale_entry[2] = 0;
			cpsw_ale_write_entry(sc, i, ale_entry);
		}
	}
}