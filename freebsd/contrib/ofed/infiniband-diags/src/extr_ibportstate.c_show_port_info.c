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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ib_portid_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  IB_PORT_LID_F ; 
 int /*<<< orphan*/  IB_PORT_LINK_SPEED_ACTIVE_F ; 
 int /*<<< orphan*/  IB_PORT_LINK_SPEED_ENABLED_F ; 
 int /*<<< orphan*/  IB_PORT_LINK_SPEED_EXT_ACTIVE_F ; 
 int /*<<< orphan*/  IB_PORT_LINK_SPEED_EXT_ENABLED_F ; 
 int /*<<< orphan*/  IB_PORT_LINK_SPEED_EXT_SUPPORTED_F ; 
 int /*<<< orphan*/  IB_PORT_LINK_SPEED_SUPPORTED_F ; 
 int /*<<< orphan*/  IB_PORT_LINK_WIDTH_ACTIVE_F ; 
 int /*<<< orphan*/  IB_PORT_LINK_WIDTH_ENABLED_F ; 
 int /*<<< orphan*/  IB_PORT_LINK_WIDTH_SUPPORTED_F ; 
 int /*<<< orphan*/  IB_PORT_LMC_F ; 
 int /*<<< orphan*/  IB_PORT_MKEY_F ; 
 int /*<<< orphan*/  IB_PORT_MKEY_LEASE_F ; 
 int /*<<< orphan*/  IB_PORT_MKEY_PROT_BITS_F ; 
 int /*<<< orphan*/  IB_PORT_SMLID_F ; 
 int /*<<< orphan*/  NOT_DISPLAYED_STR ; 
 int /*<<< orphan*/  mad_decode_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mad_dump_field (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  mad_dump_portstates (char*,int,int /*<<< orphan*/ *,int) ; 
 char* portid2str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,int,char*) ; 
 scalar_t__ show_keys ; 
 int /*<<< orphan*/  snprint_field (char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void show_port_info(ib_portid_t * dest, uint8_t * data, int portnum,
			   int espeed_cap, int is_switch)
{
	char buf[2300];
	char val[64];

	mad_dump_portstates(buf, sizeof buf, data, sizeof *data);
	mad_decode_field(data, IB_PORT_LID_F, val);
	mad_dump_field(IB_PORT_LID_F, buf + strlen(buf),
		       sizeof buf - strlen(buf), val);
	sprintf(buf + strlen(buf), "%s", "\n");
	mad_decode_field(data, IB_PORT_SMLID_F, val);
	mad_dump_field(IB_PORT_SMLID_F, buf + strlen(buf),
		       sizeof buf - strlen(buf), val);
	sprintf(buf + strlen(buf), "%s", "\n");
	mad_decode_field(data, IB_PORT_LMC_F, val);
	mad_dump_field(IB_PORT_LMC_F, buf + strlen(buf),
		       sizeof buf - strlen(buf), val);
	sprintf(buf + strlen(buf), "%s", "\n");
	mad_decode_field(data, IB_PORT_LINK_WIDTH_SUPPORTED_F, val);
	mad_dump_field(IB_PORT_LINK_WIDTH_SUPPORTED_F, buf + strlen(buf),
		       sizeof buf - strlen(buf), val);
	sprintf(buf + strlen(buf), "%s", "\n");
	mad_decode_field(data, IB_PORT_LINK_WIDTH_ENABLED_F, val);
	mad_dump_field(IB_PORT_LINK_WIDTH_ENABLED_F, buf + strlen(buf),
		       sizeof buf - strlen(buf), val);
	sprintf(buf + strlen(buf), "%s", "\n");
	mad_decode_field(data, IB_PORT_LINK_WIDTH_ACTIVE_F, val);
	mad_dump_field(IB_PORT_LINK_WIDTH_ACTIVE_F, buf + strlen(buf),
		       sizeof buf - strlen(buf), val);
	sprintf(buf + strlen(buf), "%s", "\n");
	mad_decode_field(data, IB_PORT_LINK_SPEED_SUPPORTED_F, val);
	mad_dump_field(IB_PORT_LINK_SPEED_SUPPORTED_F, buf + strlen(buf),
		       sizeof buf - strlen(buf), val);
	sprintf(buf + strlen(buf), "%s", "\n");
	mad_decode_field(data, IB_PORT_LINK_SPEED_ENABLED_F, val);
	mad_dump_field(IB_PORT_LINK_SPEED_ENABLED_F, buf + strlen(buf),
		       sizeof buf - strlen(buf), val);
	sprintf(buf + strlen(buf), "%s", "\n");
	mad_decode_field(data, IB_PORT_LINK_SPEED_ACTIVE_F, val);
	mad_dump_field(IB_PORT_LINK_SPEED_ACTIVE_F, buf + strlen(buf),
		       sizeof buf - strlen(buf), val);
	sprintf(buf + strlen(buf), "%s", "\n");
	if (espeed_cap) {
		mad_decode_field(data, IB_PORT_LINK_SPEED_EXT_SUPPORTED_F, val);
		mad_dump_field(IB_PORT_LINK_SPEED_EXT_SUPPORTED_F,
			       buf + strlen(buf), sizeof buf - strlen(buf),
			       val);
		sprintf(buf + strlen(buf), "%s", "\n");
		mad_decode_field(data, IB_PORT_LINK_SPEED_EXT_ENABLED_F, val);
		mad_dump_field(IB_PORT_LINK_SPEED_EXT_ENABLED_F,
			       buf + strlen(buf), sizeof buf - strlen(buf),
			       val);
		sprintf(buf + strlen(buf), "%s", "\n");
		mad_decode_field(data, IB_PORT_LINK_SPEED_EXT_ACTIVE_F, val);
		mad_dump_field(IB_PORT_LINK_SPEED_EXT_ACTIVE_F,
			       buf + strlen(buf), sizeof buf - strlen(buf),
			       val);
		sprintf(buf + strlen(buf), "%s", "\n");
	}
	if (!is_switch || portnum == 0) {
		if (show_keys) {
			mad_decode_field(data, IB_PORT_MKEY_F, val);
			mad_dump_field(IB_PORT_MKEY_F, buf + strlen(buf),
				       sizeof buf - strlen(buf), val);
		} else
			snprint_field(buf+strlen(buf), sizeof(buf)-strlen(buf),
				      IB_PORT_MKEY_F, 32, NOT_DISPLAYED_STR);
		sprintf(buf+strlen(buf), "%s", "\n");
		mad_decode_field(data, IB_PORT_MKEY_LEASE_F, val);
		mad_dump_field(IB_PORT_MKEY_LEASE_F, buf + strlen(buf),
			       sizeof buf - strlen(buf), val);
		sprintf(buf+strlen(buf), "%s", "\n");
		mad_decode_field(data, IB_PORT_MKEY_PROT_BITS_F, val);
		mad_dump_field(IB_PORT_MKEY_PROT_BITS_F, buf + strlen(buf),
			       sizeof buf - strlen(buf), val);
		sprintf(buf+strlen(buf), "%s", "\n");
	}

	printf("# Port info: %s port %d\n%s", portid2str(dest), portnum, buf);
}