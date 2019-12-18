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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tm ;
struct weekdays {int** names; } ;
struct tm {int tm_wday; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wcsftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  wcsncat (int*,char*,int) ; 
 int wcswidth (char*,int) ; 
 int /*<<< orphan*/  wmemset (int*,int,int) ; 

__attribute__((used)) static void
mkweekdays(struct weekdays *wds)
{
	int i, len, width = 0;
	struct tm tm;
	wchar_t buf[20];

	memset(&tm, 0, sizeof(tm));

	for (i = 0; i != 7; i++) {
		tm.tm_wday = (i+1) % 7;
		wcsftime(buf, sizeof(buf)/sizeof(buf[0]), L"%a", &tm);
		for (len = 2; len > 0; --len) {
			if ((width = wcswidth(buf, len)) <= 2)
				break;
		}
		wmemset(wds->names[i], L'\0', 4);
		if (width == 1)
			wds->names[i][0] = L' ';
		wcsncat(wds->names[i], buf, len);
		wcsncat(wds->names[i], L" ", 1);
	}
}