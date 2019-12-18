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

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  MB_LEN_MAX ; 
 int /*<<< orphan*/  dflag ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ fflag ; 
 scalar_t__ iswalnum (int) ; 
 int* malloc (int) ; 
 size_t mbrtowc (int*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 int towlower (int) ; 
 int* wcschr (int*,int) ; 

__attribute__((used)) static wchar_t *
prepkey(const char *string, wchar_t termchar)
{
	const char *readp;
	wchar_t *key, *writep;
	wchar_t ch;
	size_t clen;

	/*
	 * Reformat search string and convert to wide character representation
	 * to avoid doing it multiple times later.
	 */
	if ((key = malloc(sizeof(wchar_t) * (strlen(string) + 1))) == NULL)
		err(2, NULL);
	readp = string;
	writep = key;
	while ((clen = mbrtowc(&ch, readp, MB_LEN_MAX, NULL)) != 0) {
		if (clen == (size_t)-1 || clen == (size_t)-2)
			errc(2, EILSEQ, NULL);
		if (fflag)
			ch = towlower(ch);
		if (!dflag || iswalnum(ch))
			*writep++ = ch;
		readp += clen;
	}
	*writep = L'\0';
	if (termchar != L'\0' && (writep = wcschr(key, termchar)) != NULL)
		*++writep = L'\0';
	return (key);
}