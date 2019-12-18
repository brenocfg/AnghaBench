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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 
 scalar_t__ noconst (char const*) ; 

__attribute__((used)) static char *
skipws(
	const char *ptr)
{
	while (isspace((u_char)*ptr))
		ptr++;
	return (char*)noconst(ptr);
}