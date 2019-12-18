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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 size_t INT_MAX ; 
 int /*<<< orphan*/  MB_CUR_MAX ; 
 int VIS_ALL ; 
 int VIS_OCTAL ; 
 scalar_t__ dangerous_locale () ; 
 int /*<<< orphan*/  free (char*) ; 
 int grow_dst (char**,size_t*,size_t,char**,int) ; 
 char* malloc (size_t) ; 
 int mbtowc (int*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 int vasprintf (char**,char const*,int /*<<< orphan*/ ) ; 
 char* vis (char*,char,int,int /*<<< orphan*/ ) ; 
 int wcwidth (int) ; 

__attribute__((used)) static int
vasnmprintf(char **str, size_t maxsz, int *wp, const char *fmt, va_list ap)
{
	char	*src;	/* Source string returned from vasprintf. */
	char	*sp;	/* Pointer into src. */
	char	*dst;	/* Destination string to be returned. */
	char	*dp;	/* Pointer into dst. */
	char	*tp;	/* Temporary pointer for dst. */
	size_t	 sz;	/* Number of bytes allocated for dst. */
	wchar_t	 wc;	/* Wide character at sp. */
	int	 len;	/* Number of bytes in the character at sp. */
	int	 ret;	/* Number of bytes needed to format src. */
	int	 width;	/* Display width of the character wc. */
	int	 total_width, max_width, print;

	src = NULL;
	if ((ret = vasprintf(&src, fmt, ap)) <= 0)
		goto fail;

	sz = strlen(src) + 1;
	if ((dst = malloc(sz)) == NULL) {
		free(src);
		ret = -1;
		goto fail;
	}

	if (maxsz > INT_MAX)
		maxsz = INT_MAX;

	sp = src;
	dp = dst;
	ret = 0;
	print = 1;
	total_width = 0;
	max_width = wp == NULL ? INT_MAX : *wp;
	while (*sp != '\0') {
		if ((len = mbtowc(&wc, sp, MB_CUR_MAX)) == -1) {
			(void)mbtowc(NULL, NULL, MB_CUR_MAX);
			if (dangerous_locale()) {
				ret = -1;
				break;
			}
			len = 1;
			width = -1;
		} else if (wp == NULL &&
		    (wc == L'\n' || wc == L'\r' || wc == L'\t')) {
			/*
			 * Don't use width uninitialized; the actual
			 * value doesn't matter because total_width
			 * is only returned for wp != NULL.
			 */
			width = 0;
		} else if ((width = wcwidth(wc)) == -1 &&
		    dangerous_locale()) {
			ret = -1;
			break;
		}

		/* Valid, printable character. */

		if (width >= 0) {
			if (print && (dp - dst >= (int)maxsz - len ||
			    total_width > max_width - width))
				print = 0;
			if (print) {
				if (grow_dst(&dst, &sz, maxsz,
				    &dp, len) == -1) {
					ret = -1;
					break;
				}
				total_width += width;
				memcpy(dp, sp, len);
				dp += len;
			}
			sp += len;
			if (ret >= 0)
				ret += len;
			continue;
		}

		/* Escaping required. */

		while (len > 0) {
			if (print && (dp - dst >= (int)maxsz - 4 ||
			    total_width > max_width - 4))
				print = 0;
			if (print) {
				if (grow_dst(&dst, &sz, maxsz,
				    &dp, 4) == -1) {
					ret = -1;
					break;
				}
				tp = vis(dp, *sp, VIS_OCTAL | VIS_ALL, 0);
				width = tp - dp;
				total_width += width;
				dp = tp;
			} else
				width = 4;
			len--;
			sp++;
			if (ret >= 0)
				ret += width;
		}
		if (len > 0)
			break;
	}
	free(src);
	*dp = '\0';
	*str = dst;
	if (wp != NULL)
		*wp = total_width;

	/*
	 * If the string was truncated by the width limit but
	 * would have fit into the size limit, the only sane way
	 * to report the problem is using the return value, such
	 * that the usual idiom "if (ret < 0 || ret >= sz) error"
	 * works as expected.
	 */

	if (ret < (int)maxsz && !print)
		ret = -1;
	return ret;

fail:
	if (wp != NULL)
		*wp = 0;
	if (ret == 0) {
		*str = src;
		return 0;
	} else {
		*str = NULL;
		return -1;
	}
}