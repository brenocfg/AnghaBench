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
typedef  int wchar_t ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  mbs ;

/* Variables and functions */
 int /*<<< orphan*/  MB_LEN_MAX ; 
 scalar_t__** gargv ; 
 int mbrtowc (int*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
asciicode(void)
{
	int ch;
	wchar_t wch;
	mbstate_t mbs;

	ch = (unsigned char)**gargv;
	if (ch == '\'' || ch == '"') {
		memset(&mbs, 0, sizeof(mbs));
		switch (mbrtowc(&wch, *gargv + 1, MB_LEN_MAX, &mbs)) {
		case (size_t)-2:
		case (size_t)-1:
			wch = (unsigned char)gargv[0][1];
			break;
		case 0:
			wch = 0;
			break;
		}
		ch = wch;
	}
	++gargv;
	return (ch);
}