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
typedef  char u_char ;

/* Variables and functions */
 int /*<<< orphan*/  WIN_CHARS ; 
 int howmany (size_t,int /*<<< orphan*/ ) ; 

int
winSlotCnt(const u_char *un, size_t unlen)
{
	const u_char *cp;

	/*
	 * Drop trailing blanks and dots
	 */
	for (cp = un + unlen; unlen > 0; unlen--)
		if (*--cp != ' ' && *cp != '.')
			break;

	return howmany(unlen, WIN_CHARS);
}