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
struct stat {int /*<<< orphan*/  st_dev; int /*<<< orphan*/  st_ino; } ;
struct reqfile {char const* name; int /*<<< orphan*/  consumers; int /*<<< orphan*/  fsid; int /*<<< orphan*/  fileid; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static int
addfile(const char *path, struct reqfile *reqfile)
{
	struct stat sb;

	assert(path);
	if (stat(path, &sb) != 0) {
		warn("%s", path);
		return (1);
	}
	reqfile->fileid = sb.st_ino;
	reqfile->fsid = sb.st_dev;
	reqfile->name = path;
	STAILQ_INIT(&reqfile->consumers);
	return (0);
}