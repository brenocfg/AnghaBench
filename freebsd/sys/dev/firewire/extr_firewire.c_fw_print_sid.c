#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int phy_id; int link_active; int gap_count; int phy_speed; int contender; int power_class; int port0; int port1; int port2; int initiated_reset; int more_packets; scalar_t__ sequel; } ;
struct TYPE_5__ {scalar_t__ sequence_num; int phy_id; int port3; int port4; int port5; int port6; int port7; int port8; int port9; int port10; } ;
struct TYPE_4__ {scalar_t__ sequence_num; int phy_id; int port11; int port12; int port13; int port14; int port15; } ;
union fw_self_id {TYPE_3__ p0; TYPE_2__ p1; TYPE_1__ p2; } ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ FW_SELF_ID_PAGE0 ; 
 scalar_t__ FW_SELF_ID_PAGE1 ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 

__attribute__((used)) static void
fw_print_sid(uint32_t sid)
{
	union fw_self_id *s;
	s = (union fw_self_id *) &sid;
	if (s->p0.sequel) {
		if (s->p1.sequence_num == FW_SELF_ID_PAGE0) {
			printf("node:%d p3:%d p4:%d p5:%d p6:%d p7:%d"
			    "p8:%d p9:%d p10:%d\n",
			    s->p1.phy_id, s->p1.port3, s->p1.port4,
			    s->p1.port5, s->p1.port6, s->p1.port7,
			    s->p1.port8, s->p1.port9, s->p1.port10);
		} else if (s->p2.sequence_num == FW_SELF_ID_PAGE1) {
			printf("node:%d p11:%d p12:%d p13:%d p14:%d p15:%d\n",
			    s->p2.phy_id, s->p2.port11, s->p2.port12,
			    s->p2.port13, s->p2.port14, s->p2.port15);
		} else {
			printf("node:%d Unknown Self ID Page number %d\n",
			    s->p1.phy_id, s->p1.sequence_num);
		}
	} else {
		printf("node:%d link:%d gap:%d spd:%d con:%d pwr:%d"
		    " p0:%d p1:%d p2:%d i:%d m:%d\n",
		    s->p0.phy_id, s->p0.link_active, s->p0.gap_count,
		    s->p0.phy_speed, s->p0.contender,
		    s->p0.power_class, s->p0.port0, s->p0.port1,
		    s->p0.port2, s->p0.initiated_reset, s->p0.more_packets);
	}
}