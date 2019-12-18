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
struct igmp_ifinfo {int igi_version; int igi_rv; int igi_qi; int igi_qri; int igi_uri; int igi_v1_timer; int igi_v2_timer; int igi_v3_timer; scalar_t__ igi_flags; } ;

/* Variables and functions */
#define  IGMP_VERSION_1 130 
#define  IGMP_VERSION_2 129 
#define  IGMP_VERSION_3 128 
 int /*<<< orphan*/  printb (char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int vflag ; 

__attribute__((used)) static void
in_ifinfo(struct igmp_ifinfo *igi)
{

	printf("\t");
	switch (igi->igi_version) {
	case IGMP_VERSION_1:
	case IGMP_VERSION_2:
	case IGMP_VERSION_3:
		printf("igmpv%d", igi->igi_version);
		break;
	default:
		printf("igmpv?(%d)", igi->igi_version);
		break;
	}
	if (igi->igi_flags)
		printb(" flags", igi->igi_flags, "\020\1SILENT\2LOOPBACK");
	if (igi->igi_version == IGMP_VERSION_3) {
		printf(" rv %u qi %u qri %u uri %u",
		    igi->igi_rv, igi->igi_qi, igi->igi_qri, igi->igi_uri);
	}
	if (vflag >= 2) {
		printf(" v1timer %u v2timer %u v3timer %u",
		    igi->igi_v1_timer, igi->igi_v2_timer, igi->igi_v3_timer);
	}
	printf("\n");
}