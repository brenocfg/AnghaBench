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
typedef  int /*<<< orphan*/  timeout ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  le16enc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ set_bootvar (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
handle_timeout(int to)
{
	uint16_t timeout;

	le16enc(&timeout, to);
	if (set_bootvar("Timeout", (uint8_t *)&timeout, sizeof(timeout)) < 0)
		errx(1, "Can't set Timeout for booting.");
}