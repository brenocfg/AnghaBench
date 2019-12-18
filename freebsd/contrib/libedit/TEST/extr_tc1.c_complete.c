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
struct dirent {int /*<<< orphan*/ * d_name; } ;
struct TYPE_3__ {char* cursor; char const* buffer; } ;
typedef  TYPE_1__ LineInfo ;
typedef  int /*<<< orphan*/  EditLine ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int CC_ERROR ; 
 int CC_REFRESH ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int el_insertstr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* el_line (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static unsigned char
complete(EditLine *el, int ch)
{
	DIR *dd = opendir(".");
	struct dirent *dp;
	const char* ptr;
	const LineInfo *lf = el_line(el);
	int len;
	int res = CC_ERROR;

	/*
	 * Find the last word
	 */
	for (ptr = lf->cursor - 1;
	    !isspace((unsigned char)*ptr) && ptr > lf->buffer; ptr--)
		continue;
	len = lf->cursor - ++ptr;

	for (dp = readdir(dd); dp != NULL; dp = readdir(dd)) {
		if (len > strlen(dp->d_name))
			continue;
		if (strncmp(dp->d_name, ptr, len) == 0) {
			if (el_insertstr(el, &dp->d_name[len]) == -1)
				res = CC_ERROR;
			else
				res = CC_REFRESH;
			break;
		}
	}

	closedir(dd);
	return res;
}