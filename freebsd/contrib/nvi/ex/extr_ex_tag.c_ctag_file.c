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
struct stat {int dummy; } ;
struct TYPE_3__ {char* name; } ;
typedef  TYPE_1__ TAGF ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  free (char*) ; 
 char* join (char*,char*) ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 size_t strlen (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void
ctag_file(SCR *sp, TAGF *tfp, char *name, char **dirp, size_t *dlenp)
{
	struct stat sb;
	char *p, *buf;

	/*
	 * !!!
	 * If the tag file path is a relative path, see if it exists.  If it
	 * doesn't, look relative to the tags file path.  It's okay for a tag
	 * file to not exist, and historically, vi simply displayed a "new"
	 * file.  However, if the path exists relative to the tag file, it's
	 * pretty clear what's happening, so we may as well get it right.
	 */
	*dlenp = 0;
	if (name[0] != '/' &&
	    stat(name, &sb) && (p = strrchr(tfp->name, '/')) != NULL) {
		*p = '\0';
		if ((buf = join(tfp->name, name)) == NULL) {
			msgq(sp, M_SYSERR, NULL);
			return;
		}
		if (stat(buf, &sb) == 0) {
			*dirp = tfp->name;
			*dlenp = strlen(*dirp);
		}
		free(buf);
		*p = '/';
	}
}