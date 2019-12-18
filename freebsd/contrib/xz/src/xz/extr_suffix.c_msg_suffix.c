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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  message_warning (int /*<<< orphan*/ ,char const*,char const*) ; 

__attribute__((used)) static void
msg_suffix(const char *src_name, const char *suffix)
{
	message_warning(_("%s: File already has `%s' suffix, skipping"),
			src_name, suffix);
	return;
}