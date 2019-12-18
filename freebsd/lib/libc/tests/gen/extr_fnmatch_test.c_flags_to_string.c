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
typedef  int /*<<< orphan*/  flagnames ;

/* Variables and functions */
#define  FNM_CASEFOLD 132 
#define  FNM_LEADING_DIR 131 
#define  FNM_NOESCAPE 130 
#define  FNM_PATHNAME 129 
#define  FNM_PERIOD 128 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static const char *
flags_to_string(int flags)
{
	static const int flagvalues[] = { FNM_NOESCAPE, FNM_PATHNAME,
		FNM_PERIOD, FNM_LEADING_DIR, FNM_CASEFOLD, 0 };
	static const char flagnames[] = "FNM_NOESCAPE\0FNM_PATHNAME\0FNM_PERIOD\0FNM_LEADING_DIR\0FNM_CASEFOLD\0";
	static char result[sizeof(flagnames) + 3 * sizeof(int) + 2];
	char *p;
	size_t i, len;
	const char *fp;

	p = result;
	fp = flagnames;
	for (i = 0; flagvalues[i] != 0; i++) {
		len = strlen(fp);
		if (flags & flagvalues[i]) {
			if (p != result)
				*p++ = '|';
			memcpy(p, fp, len);
			p += len;
			flags &= ~flagvalues[i];
		}
		fp += len + 1;
	}
	if (p == result)
		memcpy(p, "0", 2);
	else if (flags != 0)
		sprintf(p, "%d", flags);
	else
		*p = '\0';
	return result;
}