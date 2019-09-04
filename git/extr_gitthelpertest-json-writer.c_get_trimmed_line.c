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
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int strlen (char*) ; 

__attribute__((used)) static char *get_trimmed_line(char *buf, int buf_size)
{
	int len;

	if (!fgets(buf, buf_size, stdin))
		return NULL;

	len = strlen(buf);
	while (len > 0) {
		char c = buf[len - 1];
		if (c == '\n' || c == '\r' || c == ' ' || c == '\t')
			buf[--len] = 0;
		else
			break;
	}

	while (*buf == ' ' || *buf == '\t')
		buf++;

	return buf;
}