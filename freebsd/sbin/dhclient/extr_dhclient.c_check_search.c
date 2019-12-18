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
 int PERIOD ; 
 int /*<<< orphan*/  borderchar (int) ; 
 int /*<<< orphan*/  middlechar (int) ; 
 scalar_t__ periodchar (int) ; 
 int strlen (char const*) ; 
 scalar_t__ whitechar (int) ; 

int
check_search(const char *srch)
{
        int pch = PERIOD, ch = *srch++;
	int domains = 1;

	/* 256 char limit re resolv.conf(5) */
	if (strlen(srch) > 256)
		return (0);

	while (whitechar(ch))
		ch = *srch++;

        while (ch != '\0') {
                int nch = *srch++;

                if (periodchar(ch) || whitechar(ch)) {
                        ;
                } else if (periodchar(pch)) {
                        if (!borderchar(ch))
                                return (0);
                } else if (periodchar(nch) || nch == '\0') {
                        if (!borderchar(ch))
                                return (0);
                } else {
                        if (!middlechar(ch))
                                return (0);
                }
		if (!whitechar(ch)) {
			pch = ch;
		} else {
			while (whitechar(nch)) {
				nch = *srch++;
			}
			if (nch != '\0')
				domains++;
			pch = PERIOD;
		}
		ch = nch;
        }
	/* 6 domain limit re resolv.conf(5) */
	if (domains > 6)
		return (0);
        return (1);
}