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
 char* DEFAULTPAGER ; 
 scalar_t__ EMPTYSTRING (char const*) ; 
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int /*<<< orphan*/  another (int*,char***,char*) ; 
 int code ; 
 int /*<<< orphan*/  free (char*) ; 
 char* ftp_malloc (size_t) ; 
 char* getoptionvalue (char*) ; 
 char* globulize (char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  system (char*) ; 

void
lpage(int argc, char *argv[])
{
	size_t len;
	const char *p;
	char *pager, *locfile;

	if (argc == 0 || argc > 2 ||
	    (argc == 1 && !another(&argc, &argv, "local-file"))) {
		UPRINTF("usage: %s local-file\n", argv[0]);
		code = -1;
		return;
	}
	if ((locfile = globulize(argv[1])) == NULL) {
		code = -1;
		return;
	}
	p = getoptionvalue("pager");
	if (EMPTYSTRING(p))
		p = DEFAULTPAGER;
	len = strlen(p) + strlen(locfile) + 2;
	pager = ftp_malloc(len);
	(void)strlcpy(pager, p,		len);
	(void)strlcat(pager, " ",	len);
	(void)strlcat(pager, locfile,	len);
	system(pager);
	code = 0;
	(void)free(pager);
	(void)free(locfile);
}