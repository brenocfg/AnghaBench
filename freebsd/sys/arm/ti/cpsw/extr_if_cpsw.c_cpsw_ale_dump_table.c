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
typedef  int uint32_t ;
struct cpsw_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_MCAST (int*) ; 
 int ALE_PORTS (int*) ; 
 int const ALE_TYPE (int*) ; 
#define  ALE_TYPE_ADDR 130 
#define  ALE_TYPE_VLAN 129 
#define  ALE_TYPE_VLAN_ADDR 128 
 int ALE_VLAN (int*) ; 
 int ALE_VLAN_MEMBERS (int*) ; 
 int ALE_VLAN_REGFLOOD (int*) ; 
 int ALE_VLAN_UNREGFLOOD (int*) ; 
 int ALE_VLAN_UNTAG (int*) ; 
 int CPSW_MAX_ALE_ENTRIES ; 
 int /*<<< orphan*/  cpsw_ale_read_entry (struct cpsw_softc*,int,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
cpsw_ale_dump_table(struct cpsw_softc *sc) {
	int i;
	uint32_t ale_entry[3];
	for (i = 0; i < CPSW_MAX_ALE_ENTRIES; i++) {
		cpsw_ale_read_entry(sc, i, ale_entry);
		switch (ALE_TYPE(ale_entry)) {
		case ALE_TYPE_VLAN:
			printf("ALE[%4u] %08x %08x %08x ", i, ale_entry[2],
				ale_entry[1], ale_entry[0]);
			printf("type: %u ", ALE_TYPE(ale_entry));
			printf("vlan: %u ", ALE_VLAN(ale_entry));
			printf("untag: %u ", ALE_VLAN_UNTAG(ale_entry));
			printf("reg flood: %u ", ALE_VLAN_REGFLOOD(ale_entry));
			printf("unreg flood: %u ", ALE_VLAN_UNREGFLOOD(ale_entry));
			printf("members: %u ", ALE_VLAN_MEMBERS(ale_entry));
			printf("\n");
			break;
		case ALE_TYPE_ADDR:
		case ALE_TYPE_VLAN_ADDR:
			printf("ALE[%4u] %08x %08x %08x ", i, ale_entry[2],
				ale_entry[1], ale_entry[0]);
			printf("type: %u ", ALE_TYPE(ale_entry));
			printf("mac: %02x:%02x:%02x:%02x:%02x:%02x ",
				(ale_entry[1] >> 8) & 0xFF,
				(ale_entry[1] >> 0) & 0xFF,
				(ale_entry[0] >>24) & 0xFF,
				(ale_entry[0] >>16) & 0xFF,
				(ale_entry[0] >> 8) & 0xFF,
				(ale_entry[0] >> 0) & 0xFF);
			printf(ALE_MCAST(ale_entry) ? "mcast " : "ucast ");
			if (ALE_TYPE(ale_entry) == ALE_TYPE_VLAN_ADDR)
				printf("vlan: %u ", ALE_VLAN(ale_entry));
			printf("port: %u ", ALE_PORTS(ale_entry));
			printf("\n");
			break;
		}
	}
	printf("\n");
}