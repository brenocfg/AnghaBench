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
typedef  int /*<<< orphan*/  romid_t ;
typedef  int /*<<< orphan*/  romid ;

/* Variables and functions */
 scalar_t__ ow_crc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ow_check_crc(romid_t romid)
{
	return ow_crc(NULL, NULL, (uint8_t *)&romid, sizeof(romid)) == 0;
}