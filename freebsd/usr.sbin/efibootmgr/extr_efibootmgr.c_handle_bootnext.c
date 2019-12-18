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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  le16enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ set_bootvar (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
handle_bootnext(uint16_t bootnum)
{
	uint16_t num;

	le16enc(&num, bootnum);
	if (set_bootvar("BootNext", (uint8_t*)&bootnum, sizeof(uint16_t)) < 0)
		err(1, "set_bootvar");
}