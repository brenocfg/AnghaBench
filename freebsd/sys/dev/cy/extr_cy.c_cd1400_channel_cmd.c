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
struct com_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CD1400_CCR ; 
 int /*<<< orphan*/  cd1400_channel_cmd_wait (struct com_s*) ; 
 int /*<<< orphan*/  cd_setreg (struct com_s*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cd1400_channel_cmd(struct com_s *com, int cmd)
{
	cd1400_channel_cmd_wait(com);
	cd_setreg(com, CD1400_CCR, cmd);
	cd1400_channel_cmd_wait(com);
}