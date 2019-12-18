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
 int /*<<< orphan*/  isprint (char const) ; 

__attribute__((used)) static int
nameok(const char name[16])
{
	int i;

	/* descriptor names are null-terminated printable ascii */
	for (i = 0; i < 15; i++)
		if (!isprint(name[i]))
			break;
	return (name[i] == '\0');
}