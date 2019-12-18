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
struct url_stat {int size; int /*<<< orphan*/  mtime; int /*<<< orphan*/  atime; } ;
struct stat {int st_size; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; } ;

/* Variables and functions */
 int /*<<< orphan*/  fetch_syserr () ; 
 int stat (char const*,struct stat*) ; 

__attribute__((used)) static int
fetch_stat_file(const char *fn, struct url_stat *us)
{
	struct stat sb;

	us->size = -1;
	us->atime = us->mtime = 0;
	if (stat(fn, &sb) == -1) {
		fetch_syserr();
		return (-1);
	}
	us->size = sb.st_size;
	us->atime = sb.st_atime;
	us->mtime = sb.st_mtime;
	return (0);
}