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

/* Variables and functions */
 int IB_PORT_CAPMASK2_F ; 
 int IB_PORT_FIRST_F ; 
 int IB_PORT_LAST_F ; 
 int IB_PORT_LINK_SPEED_EXT_LAST_F ; 
 int IB_PORT_MKEY_F ; 
 int /*<<< orphan*/  NOT_DISPLAYED_STR ; 
 int /*<<< orphan*/  mad_decode_field (void*,int,char*) ; 
 int /*<<< orphan*/  mad_dump_field (int,char*,int,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ show_keys ; 
 int /*<<< orphan*/  snprint_field (char*,int,int,int,int /*<<< orphan*/ ) ; 

void dump_portinfo(void *pi, int tabs)
{
	int field, i;
	char val[64];
	char buf[1024];

	for (field = IB_PORT_FIRST_F; field < IB_PORT_LAST_F; field++) {
		for (i=0;i<tabs;i++)
			printf("\t");
		if (field == IB_PORT_MKEY_F && show_keys == 0) {
			snprint_field(buf, 1024, field, 32, NOT_DISPLAYED_STR);
		} else {
			mad_decode_field(pi, field, val);
			if (!mad_dump_field(field, buf, 1024, val))
				return;
		}
		printf("%s\n", buf);
	}

	for (field = IB_PORT_CAPMASK2_F;
	     field < IB_PORT_LINK_SPEED_EXT_LAST_F; field++) {
		for (i=0;i<tabs;i++)
			printf("\t");
		mad_decode_field(pi, field, val);
		if (!mad_dump_field(field, buf, 1024, val))
			return;
		printf("%s\n", buf);
	}
}