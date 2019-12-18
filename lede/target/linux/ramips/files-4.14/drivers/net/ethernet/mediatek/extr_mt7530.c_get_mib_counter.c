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
typedef  int u64 ;
struct mt7530_priv {int dummy; } ;
struct TYPE_2__ {int size; scalar_t__ offset; } ;

/* Variables and functions */
 int MT7621_MIB_COUNTER_BASE ; 
 int MT7621_MIB_COUNTER_PORT_OFFSET ; 
 int mt7530_r32 (struct mt7530_priv*,scalar_t__) ; 
 TYPE_1__* mt7621_mibs ; 

__attribute__((used)) static u64 get_mib_counter(struct mt7530_priv *priv, int i, int port)
{
	unsigned int port_base;
	u64 lo;

	port_base = MT7621_MIB_COUNTER_BASE +
		    MT7621_MIB_COUNTER_PORT_OFFSET * port;

	lo = mt7530_r32(priv, port_base + mt7621_mibs[i].offset);
	if (mt7621_mibs[i].size == 2) {
		u64 hi;

		hi = mt7530_r32(priv, port_base + mt7621_mibs[i].offset + 4);
		lo |= hi << 32;
	}

	return lo;
}