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
struct ow_cmd {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONVERT_T ; 
 int /*<<< orphan*/  own_command_wait (int /*<<< orphan*/ ,struct ow_cmd*) ; 
 int /*<<< orphan*/  own_self_command (int /*<<< orphan*/ ,struct ow_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ow_temp_convert_t(device_t dev)
{
	struct ow_cmd cmd;

	own_self_command(dev, &cmd, CONVERT_T);
	own_command_wait(dev, &cmd);

	return 0;
}