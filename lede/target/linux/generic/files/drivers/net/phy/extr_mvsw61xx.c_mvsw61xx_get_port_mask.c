#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_2__ {char* s; } ;
struct switch_val {int port_vlan; TYPE_1__ value; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int dummy; } ;
struct mvsw61xx_state {char* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV_PORTREG (int /*<<< orphan*/ ,int) ; 
 int MV_PORTS ; 
 int MV_PORTS_MASK ; 
 int /*<<< orphan*/  VLANMAP ; 
 struct mvsw61xx_state* get_state (struct switch_dev*) ; 
 int sprintf (char*,char*,int) ; 
 int sr16 (struct switch_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mvsw61xx_get_port_mask(struct switch_dev *dev,
		const struct switch_attr *attr, struct switch_val *val)
{
	struct mvsw61xx_state *state = get_state(dev);
	char *buf = state->buf;
	int port, len, i;
	u16 reg;

	port = val->port_vlan;
	reg = sr16(dev, MV_PORTREG(VLANMAP, port)) & MV_PORTS_MASK;

	len = sprintf(buf, "0x%04x: ", reg);

	for (i = 0; i < MV_PORTS; i++) {
		if (reg & (1 << i))
			len += sprintf(buf + len, "%d ", i);
		else if (i == port)
			len += sprintf(buf + len, "(%d) ", i);
	}

	val->value.s = buf;

	return 0;
}