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
 int P2SB_BUSY ; 
 int /*<<< orphan*/  P2SB_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  P2SB_STAT_OFF ; 
 int /*<<< orphan*/  word ; 

__attribute__((used)) static bool p2sb_is_busy(u16 *status)
{
	P2SB_READ(word, P2SB_STAT_OFF, status);

	return !!(*status & P2SB_BUSY);
}