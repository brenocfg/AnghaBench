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
typedef  int u32 ;
struct grpci1_priv {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int grpci1_cfg_r32 (struct grpci1_priv*,unsigned int,unsigned int,int,int*) ; 
 int grpci1_cfg_w32 (struct grpci1_priv*,unsigned int,unsigned int,int,int) ; 

__attribute__((used)) static int grpci1_cfg_w16(struct grpci1_priv *priv, unsigned int bus,
				unsigned int devfn, int where, u32 val)
{
	int ret;
	u32 v;

	if (where & 0x1)
		return -EINVAL;
	ret = grpci1_cfg_r32(priv, bus, devfn, where&~3, &v);
	if (ret)
		return ret;
	v = (v & ~(0xffff << (8 * (where & 0x3)))) |
	    ((0xffff & val) << (8 * (where & 0x3)));
	return grpci1_cfg_w32(priv, bus, devfn, where & ~0x3, v);
}