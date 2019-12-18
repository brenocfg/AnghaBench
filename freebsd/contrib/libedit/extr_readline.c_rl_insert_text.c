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
 int /*<<< orphan*/ * e ; 
 scalar_t__ el_insertstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * h ; 
 int /*<<< orphan*/  rl_initialize () ; 
 scalar_t__ strlen (char const*) ; 

int
rl_insert_text(const char *text)
{
	if (!text || *text == 0)
		return 0;

	if (h == NULL || e == NULL)
		rl_initialize();

	if (el_insertstr(e, text) < 0)
		return 0;
	return (int)strlen(text);
}