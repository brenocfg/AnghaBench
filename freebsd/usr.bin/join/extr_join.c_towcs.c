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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/ * malloc (size_t) ; 
 size_t mbsrtowcs (int /*<<< orphan*/ *,char const**,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static wchar_t *
towcs(const char *s)
{
	wchar_t *wcs;
	size_t n;

	if ((n = mbsrtowcs(NULL, &s, 0, NULL)) == (size_t)-1)
		return (NULL);
	if ((wcs = malloc((n + 1) * sizeof(*wcs))) == NULL)
		return (NULL);
	mbsrtowcs(wcs, &s, n + 1, NULL);
	return (wcs);
}