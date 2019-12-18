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
typedef  int /*<<< orphan*/  u8 ;
struct pmf_handlers {int dummy; } ;
struct pmf_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_PARSE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMF_PARSE_CALL (int /*<<< orphan*/ ,struct pmf_cmd*,struct pmf_handlers*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmf_next32 (struct pmf_cmd*) ; 
 int /*<<< orphan*/  write_gpio ; 

__attribute__((used)) static int pmf_parser_write_gpio(struct pmf_cmd *cmd, struct pmf_handlers *h)
{
	u8 value = (u8)pmf_next32(cmd);
	u8 mask = (u8)pmf_next32(cmd);

	LOG_PARSE("pmf: write_gpio(value: %02x, mask: %02x)\n", value, mask);

	PMF_PARSE_CALL(write_gpio, cmd, h, value, mask);
}