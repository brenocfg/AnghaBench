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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  PO2 (int) ; 
 int le16dec (int*) ; 

__attribute__((used)) static int
mbr_probe_bpb(u_char *bpb)
{
	uint16_t secsz;
	uint8_t clstsz;

#define PO2(x)	((x & (x - 1)) == 0)
	secsz = le16dec(bpb);
	if (secsz < 512 || secsz > 4096 || !PO2(secsz))
		return (0);
	clstsz = bpb[2];
	if (clstsz < 1 || clstsz > 128 || !PO2(clstsz))
		return (0);
#undef PO2

	return (1);
}