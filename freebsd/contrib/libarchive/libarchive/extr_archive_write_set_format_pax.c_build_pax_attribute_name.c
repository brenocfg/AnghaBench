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
 int /*<<< orphan*/  build_ustar_entry_name (char*,char const*,int,char*) ; 
 int getpid () ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *
build_pax_attribute_name(char *dest, const char *src)
{
	char buff[64];
	const char *p;

	/* Handle the null filename case. */
	if (src == NULL || *src == '\0') {
		strcpy(dest, "PaxHeader/blank");
		return (dest);
	}

	/* Prune final '/' and other unwanted final elements. */
	p = src + strlen(src);
	for (;;) {
		/* Ends in "/", remove the '/' */
		if (p > src && p[-1] == '/') {
			--p;
			continue;
		}
		/* Ends in "/.", remove the '.' */
		if (p > src + 1 && p[-1] == '.'
		    && p[-2] == '/') {
			--p;
			continue;
		}
		break;
	}

	/* Pathological case: After above, there was nothing left.
	 * This includes "/." "/./." "/.//./." etc. */
	if (p == src) {
		strcpy(dest, "/PaxHeader/rootdir");
		return (dest);
	}

	/* Convert unadorned "." into a suitable filename. */
	if (*src == '.' && p == src + 1) {
		strcpy(dest, "PaxHeader/currentdir");
		return (dest);
	}

	/*
	 * TODO: Push this string into the 'pax' structure to avoid
	 * recomputing it every time.  That will also open the door
	 * to having clients override it.
	 */
#if HAVE_GETPID && 0  /* Disable this for now; see above comment. */
	sprintf(buff, "PaxHeader.%d", getpid());
#else
	/* If the platform can't fetch the pid, don't include it. */
	strcpy(buff, "PaxHeader");
#endif
	/* General case: build a ustar-compatible name adding
	 * "/PaxHeader/". */
	build_ustar_entry_name(dest, src, p - src, buff);

	return (dest);
}