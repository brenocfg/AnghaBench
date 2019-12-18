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
typedef  int /*<<< orphan*/  uint32_t ;
struct octeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lio_dev_info (struct octeon_device*,char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
lio_dbg_console_print(struct octeon_device *oct, uint32_t console_num,
		      char *prefix, char *suffix)
{

	if (prefix != NULL && suffix != NULL)
		lio_dev_info(oct, "%u: %s%s\n", console_num, prefix, suffix);
	else if (prefix != NULL)
		lio_dev_info(oct, "%u: %s\n", console_num, prefix);
	else if (suffix != NULL)
		lio_dev_info(oct, "%u: %s\n", console_num, suffix);

	return (0);
}