#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int l_uf; int l_ui; } ;
typedef  TYPE_1__ l_fp ;

/* Variables and functions */
 int ntohl (int) ; 

l_fp
convertRefIDToLFP(uint32_t r)
{
	l_fp temp;

	r = ntohl(r);

	// printf("%03d %08x: ", (r >> 24) & 0xFF, (r & 0x00FFFFFF) );

	temp.l_uf = (r << 10);	/* 22 fractional bits */

	temp.l_ui = (r >> 22) & 0x3;
	temp.l_ui |= ~(temp.l_ui & 2) + 1;

	return temp;
}