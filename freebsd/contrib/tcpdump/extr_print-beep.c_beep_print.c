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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 scalar_t__ l_strnstart (int /*<<< orphan*/ *,char*,int,char const*,int /*<<< orphan*/ ) ; 

void
beep_print(netdissect_options *ndo, const u_char *bp, u_int length)
{

	if (l_strnstart(ndo, "MSG", 4, (const char *)bp, length)) /* A REQuest */
		ND_PRINT((ndo, " BEEP MSG"));
	else if (l_strnstart(ndo, "RPY ", 4, (const char *)bp, length))
		ND_PRINT((ndo, " BEEP RPY"));
	else if (l_strnstart(ndo, "ERR ", 4, (const char *)bp, length))
		ND_PRINT((ndo, " BEEP ERR"));
	else if (l_strnstart(ndo, "ANS ", 4, (const char *)bp, length))
		ND_PRINT((ndo, " BEEP ANS"));
	else if (l_strnstart(ndo, "NUL ", 4, (const char *)bp, length))
		ND_PRINT((ndo, " BEEP NUL"));
	else if (l_strnstart(ndo, "SEQ ", 4, (const char *)bp, length))
		ND_PRINT((ndo, " BEEP SEQ"));
	else if (l_strnstart(ndo, "END", 4, (const char *)bp, length))
		ND_PRINT((ndo, " BEEP END"));
	else
		ND_PRINT((ndo, " BEEP (payload or undecoded)"));
}