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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 scalar_t__ Strlen (int /*<<< orphan*/ *) ; 
 int TermH ; 
 unsigned int max (unsigned int,unsigned int) ; 

__attribute__((used)) static int
find_rows(Char *items[], int count, int no_file_suffix)
{
    int i, columns, rows;
    unsigned int maxwidth = 0;

    for (i = 0; i < count; i++)	/* find widest string */
	maxwidth = max(maxwidth, (unsigned int) Strlen(items[i]));

    maxwidth += no_file_suffix ? 1 : 2;	/* for the file tag and space */
    columns = (TermH + 1) / maxwidth;	/* PWP: terminal size change */
    if (!columns)
	columns = 1;
    rows = (count + (columns - 1)) / columns;

    return rows;
}