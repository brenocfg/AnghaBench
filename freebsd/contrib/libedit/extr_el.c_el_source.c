#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  elpath ;
struct TYPE_4__ {int /*<<< orphan*/  el_scratch; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ EditLine ;

/* Variables and functions */
 char* ct_decode_string (char*,int /*<<< orphan*/ *) ; 
 char* el_calloc (size_t,int) ; 
 int /*<<< orphan*/  el_free (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 void* getenv (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ issetugid () ; 
 scalar_t__ iswspace (char const) ; 
 int parse_line (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char const*) ; 
 scalar_t__ strlen (char*) ; 

int
el_source(EditLine *el, const char *fname)
{
	FILE *fp;
	size_t len;
	ssize_t slen;
	char *ptr;
	char *path = NULL;
	const wchar_t *dptr;
	int error = 0;

	fp = NULL;
	if (fname == NULL) {
#ifdef HAVE_ISSETUGID
		if (issetugid())
			return -1;

		if ((fname = getenv("EDITRC")) == NULL) {
			static const char elpath[] = "/.editrc";
			size_t plen = sizeof(elpath);

			if ((ptr = getenv("HOME")) == NULL)
				return -1;
			plen += strlen(ptr);
			if ((path = el_calloc(plen, sizeof(*path))) == NULL)
				return -1;
			(void)snprintf(path, plen, "%s%s", ptr,
				elpath + (*ptr == '\0'));
			fname = path;
		}
#else
		/*
		 * If issetugid() is missing, always return an error, in order
		 * to keep from inadvertently opening up the user to a security
		 * hole.
		 */
		return -1;
#endif
	}
	if (fname[0] == '\0')
		return -1;

	if (fp == NULL)
		fp = fopen(fname, "r");
	if (fp == NULL) {
		el_free(path);
		return -1;
	}

	ptr = NULL;
	len = 0;
	while ((slen = getline(&ptr, &len, fp)) != -1) {
		if (*ptr == '\n')
			continue;	/* Empty line. */
		if (slen > 0 && ptr[--slen] == '\n')
			ptr[slen] = '\0';

		dptr = ct_decode_string(ptr, &el->el_scratch);
		if (!dptr)
			continue;
		/* loop until first non-space char or EOL */
		while (*dptr != '\0' && iswspace(*dptr))
			dptr++;
		if (*dptr == '#')
			continue;   /* ignore, this is a comment line */
		if ((error = parse_line(el, dptr)) == -1)
			break;
	}
	free(ptr);

	el_free(path);
	(void) fclose(fp);
	return error;
}