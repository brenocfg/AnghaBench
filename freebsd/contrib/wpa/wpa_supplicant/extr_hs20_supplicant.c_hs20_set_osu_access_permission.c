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
struct stat {int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_WARNING ; 
 scalar_t__ chmod (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ lchown (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void hs20_set_osu_access_permission(const char *osu_dir,
					   const char *fname)
{
	struct stat statbuf;

	/* Get OSU directory information */
	if (stat(osu_dir, &statbuf) < 0) {
		wpa_printf(MSG_WARNING, "Cannot stat the OSU directory %s",
			   osu_dir);
		return;
	}

	if (chmod(fname, statbuf.st_mode) < 0) {
		wpa_printf(MSG_WARNING,
			   "Cannot change the permissions for %s", fname);
		return;
	}

	if (lchown(fname, statbuf.st_uid, statbuf.st_gid) < 0) {
		wpa_printf(MSG_WARNING, "Cannot change the ownership for %s",
			   fname);
	}
}