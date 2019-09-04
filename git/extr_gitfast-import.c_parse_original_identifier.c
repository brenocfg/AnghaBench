#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 TYPE_1__ command_buf ; 
 int /*<<< orphan*/  read_next_command () ; 
 scalar_t__ skip_prefix (int /*<<< orphan*/ ,char*,char const**) ; 

__attribute__((used)) static void parse_original_identifier(void)
{
	const char *v;
	if (skip_prefix(command_buf.buf, "original-oid ", &v))
		read_next_command();
}