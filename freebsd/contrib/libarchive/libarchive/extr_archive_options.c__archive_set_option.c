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
struct archive {int dummy; } ;
typedef  int (* option_handler ) (struct archive*,char const*,char const*,char const*) ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,int /*<<< orphan*/ ,char*,...) ; 

int
_archive_set_option(struct archive *a,
    const char *m, const char *o, const char *v,
    int magic, const char *fn, option_handler use_option)
{
	const char *mp, *op, *vp;
	int r;

	archive_check_magic(a, magic, ARCHIVE_STATE_NEW, fn);

	mp = (m != NULL && m[0] != '\0') ? m : NULL;
	op = (o != NULL && o[0] != '\0') ? o : NULL;
	vp = (v != NULL && v[0] != '\0') ? v : NULL;

	if (op == NULL && vp == NULL)
		return (ARCHIVE_OK);
	if (op == NULL) {
		archive_set_error(a, ARCHIVE_ERRNO_MISC, "Empty option");
		return (ARCHIVE_FAILED);
	}

	r = use_option(a, mp, op, vp);
	if (r == ARCHIVE_WARN - 1) {
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "Unknown module name: `%s'", mp);
		return (ARCHIVE_FAILED);
	}
	if (r == ARCHIVE_WARN) {
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "Undefined option: `%s%s%s%s%s%s'",
		    vp?"":"!", mp?mp:"", mp?":":"", op, vp?"=":"", vp?vp:"");
		return (ARCHIVE_FAILED);
	}
	return (r);
}