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
typedef  int u8 ;
struct cs2000_priv {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int cs2000_read (struct cs2000_priv*,int) ; 
 int cs2000_write (struct cs2000_priv*,int,int) ; 

__attribute__((used)) static int cs2000_bset(struct cs2000_priv *priv, u8 addr, u8 mask, u8 val)
{
	s32 data;

	data = cs2000_read(priv, addr);
	if (data < 0)
		return data;

	data &= ~mask;
	data |= (val & mask);

	return cs2000_write(priv, addr, data);
}