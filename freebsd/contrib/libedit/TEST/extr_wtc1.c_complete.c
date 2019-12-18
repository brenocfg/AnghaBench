#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const wchar_t ;
struct dirent {int /*<<< orphan*/ * d_name; } ;
typedef  int /*<<< orphan*/  dir ;
struct TYPE_3__ {int /*<<< orphan*/  const* cursor; int /*<<< orphan*/  const* buffer; } ;
typedef  TYPE_1__ LineInfoW ;
typedef  int /*<<< orphan*/  EditLine ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 unsigned char CC_ERROR ; 
 unsigned char CC_REFRESH ; 
 int MB_LEN_MAX ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int el_winsertstr (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 TYPE_1__* el_wline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  iswspace (int /*<<< orphan*/  const) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  mbstowcs (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  wctomb (char*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static unsigned char
complete(EditLine *el, int ch)
{
	DIR *dd = opendir(".");
	struct dirent *dp;
	const wchar_t *ptr;
	char *buf, *bptr;
	const LineInfoW *lf = el_wline(el);
	int len, mblen, i;
	unsigned char res = 0;
	wchar_t dir[1024];

	/* Find the last word */
	for (ptr = lf->cursor -1; !iswspace(*ptr) && ptr > lf->buffer; --ptr)
		continue;
	len = lf->cursor - ++ptr;

	/* Convert last word to multibyte encoding, so we can compare to it */
	wctomb(NULL, 0); /* Reset shift state */
	mblen = MB_LEN_MAX * len + 1;
	buf = bptr = malloc(mblen);
	if (buf == NULL)
		err(1, "malloc");
	for (i = 0; i < len; ++i) {
		/* Note: really should test for -1 return from wctomb */
		bptr += wctomb(bptr, ptr[i]);
	}
	*bptr = 0; /* Terminate multibyte string */
	mblen = bptr - buf;

	/* Scan directory for matching name */
	for (dp = readdir(dd); dp != NULL; dp = readdir(dd)) {
		if (mblen > strlen(dp->d_name))
			continue;
		if (strncmp(dp->d_name, buf, mblen) == 0) {
			mbstowcs(dir, &dp->d_name[mblen],
			    sizeof(dir) / sizeof(*dir));
			if (el_winsertstr(el, dir) == -1)
				res = CC_ERROR;
			else
				res = CC_REFRESH;
			break;
		}
	}

	closedir(dd);
	free(buf);
	return res;
}