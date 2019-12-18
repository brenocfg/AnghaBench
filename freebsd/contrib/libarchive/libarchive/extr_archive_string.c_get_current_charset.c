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
struct archive {char* current_code; int /*<<< orphan*/  current_oemcp; int /*<<< orphan*/  current_codepage; } ;

/* Variables and functions */
 char* default_iconv_charset (char*) ; 
 int /*<<< orphan*/  get_current_codepage () ; 
 int /*<<< orphan*/  get_current_oemcp () ; 
 char* strdup (char const*) ; 

__attribute__((used)) static const char *
get_current_charset(struct archive *a)
{
	const char *cur_charset;

	if (a == NULL)
		cur_charset = default_iconv_charset("");
	else {
		cur_charset = default_iconv_charset(a->current_code);
		if (a->current_code == NULL) {
			a->current_code = strdup(cur_charset);
			a->current_codepage = get_current_codepage();
			a->current_oemcp = get_current_oemcp();
		}
	}
	return (cur_charset);
}