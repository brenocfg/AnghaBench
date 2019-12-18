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
 int /*<<< orphan*/  INTERR ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int mb_cur_max ; 
 int to_mb (char*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int wcslen (int /*<<< orphan*/  const*) ; 

char *
to_mb_string(const wchar_t *wcs)
{
	char	*mbs;
	char	*ptr;
	int	len;

	mbs = malloc((wcslen(wcs) * mb_cur_max) + 1);
	if (mbs == NULL) {
		warn("out of memory");
		return (NULL);
	}
	ptr = mbs;
	while (*wcs) {
		if ((len = to_mb(ptr, *wcs)) < 0) {
			INTERR;
			free(mbs);
			return (NULL);
		}
		wcs++;
		ptr += len;
	}
	*ptr = 0;
	return (mbs);
}