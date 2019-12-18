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
typedef  enum ucb1x00_reset { ____Placeholder_ucb1x00_reset } ucb1x00_reset ;

/* Variables and functions */
 int /*<<< orphan*/  RST_UCB1X00 ; 
 int UCB_RST_PROBE_FAIL ; 
 int UCB_RST_REMOVE ; 
 int UCB_RST_SUSPEND ; 
 int /*<<< orphan*/  assabet_codec_reset (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void assabet_ucb1x00_reset(enum ucb1x00_reset state)
{
	int set = state == UCB_RST_REMOVE || state == UCB_RST_SUSPEND ||
		state == UCB_RST_PROBE_FAIL;
	assabet_codec_reset(RST_UCB1X00, set);
}