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
 scalar_t__ rl_completion_append_character ; 

__attribute__((used)) static const char *
/*ARGSUSED*/
_rl_completion_append_character_function(const char *dummy
    __attribute__((__unused__)))
{
	static char buf[2];
	buf[0] = (char)rl_completion_append_character;
	buf[1] = '\0';
	return buf;
}