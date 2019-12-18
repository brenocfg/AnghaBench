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
typedef  int u16 ;

/* Variables and functions */
 size_t Hi8 (int) ; 
 size_t Lo8 (int) ; 
 int* Sbox ; 

__attribute__((used)) static __inline u16 _S_(u16 v)
{
	u16 t = Sbox[Hi8(v)];
	return Sbox[Lo8(v)] ^ ((t << 8) | (t >> 8));
}