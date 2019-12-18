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
typedef  int u_int ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DEFNUM ; 
 int MAXLINELEN ; 
 int /*<<< orphan*/ ** calloc (int,int) ; 
 int entries ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int eval ; 
 scalar_t__ fgetws (int*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ iswspace (int) ; 
 int /*<<< orphan*/ ** list ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int maxlength ; 
 int /*<<< orphan*/ ** realloc (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  warnx (char*) ; 
 int* wcschr (int*,int) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ *,int*) ; 
 int wcslen (int*) ; 
 int width (int*) ; 

__attribute__((used)) static void
input(FILE *fp)
{
	static int maxentry;
	int len;
	wchar_t *p, buf[MAXLINELEN];

	if (!list)
		if ((list = calloc((maxentry = DEFNUM), sizeof(*list))) ==
		    NULL)
			err(1, NULL);
	while (fgetws(buf, MAXLINELEN, fp)) {
		for (p = buf; *p && iswspace(*p); ++p);
		if (!*p)
			continue;
		if (!(p = wcschr(p, L'\n'))) {
			warnx("line too long");
			eval = 1;
			continue;
		}
		*p = L'\0';
		len = width(buf);
		if (maxlength < len)
			maxlength = len;
		if (entries == maxentry) {
			maxentry += DEFNUM;
			if (!(list = realloc(list,
			    (u_int)maxentry * sizeof(*list))))
				err(1, NULL);
		}
		list[entries] = malloc((wcslen(buf) + 1) * sizeof(wchar_t));
		if (list[entries] == NULL)
			err(1, NULL);
		wcscpy(list[entries], buf);
		entries++;
	}
}