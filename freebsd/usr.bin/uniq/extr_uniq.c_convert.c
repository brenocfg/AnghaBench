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
 int SIZE_MAX ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ iflag ; 
 int* malloc (size_t) ; 
 size_t mbstowcs (int*,char const*,size_t) ; 
 scalar_t__ numchars ; 
 scalar_t__ numfields ; 
 int /*<<< orphan*/  skip (int*) ; 
 int towlower (int) ; 
 int* wcsdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static wchar_t *
convert(const char *str)
{
	size_t n;
	wchar_t *buf, *ret, *p;

	if ((n = mbstowcs(NULL, str, 0)) == (size_t)-1)
		return (NULL);
	if (SIZE_MAX / sizeof(*buf) < n + 1)
		errx(1, "conversion buffer length overflow");
	if ((buf = malloc((n + 1) * sizeof(*buf))) == NULL)
		err(1, "malloc");
	if (mbstowcs(buf, str, n + 1) != n)
		errx(1, "internal mbstowcs() error");
	/* The last line may not end with \n. */
	if (n > 0 && buf[n - 1] == L'\n')
		buf[n - 1] = L'\0';

	/* If requested get the chosen fields + character offsets. */
	if (numfields || numchars) {
		if ((ret = wcsdup(skip(buf))) == NULL)
			err(1, "wcsdup");
		free(buf);
	} else
		ret = buf;

	if (iflag) {
		for (p = ret; *p != L'\0'; p++)
			*p = towlower(*p);
	}

	return (ret);
}