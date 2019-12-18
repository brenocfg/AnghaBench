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
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t topspin_chassisguid(uint64_t guid)
{
	/* Byte 3 in system image GUID is chassis type, and */
	/* Byte 4 is location ID (slot) so just mask off byte 4 */
	return guid & 0xffffffff00ffffffULL;
}