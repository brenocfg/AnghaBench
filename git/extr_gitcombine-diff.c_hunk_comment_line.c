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
 scalar_t__ isalpha (int) ; 

__attribute__((used)) static int hunk_comment_line(const char *bol)
{
	int ch;

	if (!bol)
		return 0;
	ch = *bol & 0xff;
	return (isalpha(ch) || ch == '_' || ch == '$');
}