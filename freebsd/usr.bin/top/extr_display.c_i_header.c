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
 scalar_t__ ERASE ; 
 scalar_t__ OFF ; 
 scalar_t__ ON ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ header_status ; 
 int /*<<< orphan*/  lastline ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stdout ; 
 char* trim_header (char const*) ; 

void
i_header(const char *text)
{
    char *s;

    s = trim_header(text);
    if (s != NULL)
	text = s;

    if (header_status == ON)
    {
	putchar('\n');
	fputs(text, stdout);
	lastline++;
    }
    else if (header_status == ERASE)
    {
	header_status = OFF;
    }
    free(s);
}