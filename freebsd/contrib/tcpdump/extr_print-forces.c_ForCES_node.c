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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline const char *ForCES_node(uint32_t node)
{
	if (node <= 0x3FFFFFFF)
		return "FE";
	if (node >= 0x40000000 && node <= 0x7FFFFFFF)
		return "CE";
	if (node >= 0xC0000000 && node <= 0xFFFFFFEF)
		return "AllMulticast";
	if (node == 0xFFFFFFFD)
		return "AllCEsBroadcast";
	if (node == 0xFFFFFFFE)
		return "AllFEsBroadcast";
	if (node == 0xFFFFFFFF)
		return "AllBroadcast";

	return "ForCESreserved";

}