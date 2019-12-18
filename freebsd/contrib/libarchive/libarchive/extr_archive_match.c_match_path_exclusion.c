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
struct match {int /*<<< orphan*/  pattern; } ;
struct archive_match {int /*<<< orphan*/  archive; } ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int PATHMATCH_NO_ANCHOR_END ; 
 int PATHMATCH_NO_ANCHOR_START ; 
 int archive_mstring_get_mbs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**) ; 
 int archive_mstring_get_wcs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int archive_pathmatch (char const*,char const*,int) ; 
 int archive_pathmatch_w (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ errno ; 
 int error_nomem (struct archive_match*) ; 

__attribute__((used)) static int
match_path_exclusion(struct archive_match *a, struct match *m,
    int mbs, const void *pn)
{
	int flag = PATHMATCH_NO_ANCHOR_START | PATHMATCH_NO_ANCHOR_END;
	int r;

	if (mbs) {
		const char *p;
		r = archive_mstring_get_mbs(&(a->archive), &(m->pattern), &p);
		if (r == 0)
			return (archive_pathmatch(p, (const char *)pn, flag));
	} else {
		const wchar_t *p;
		r = archive_mstring_get_wcs(&(a->archive), &(m->pattern), &p);
		if (r == 0)
			return (archive_pathmatch_w(p, (const wchar_t *)pn,
				flag));
	}
	if (errno == ENOMEM)
		return (error_nomem(a));
	return (0);
}