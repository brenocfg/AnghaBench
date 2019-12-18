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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char const*,char const*,char const*) ; 

void
test_syslog_send (const char *full_msg, const char *v0_hdr,
		  const char *text_only)
{
    printf("{{%s}}\n{{%s}}\n{{%s}}\n\n", full_msg, v0_hdr, text_only);
}