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
struct tempfile {int /*<<< orphan*/ * fp; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/ * fdopen (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  is_tempfile_active (struct tempfile*) ; 

FILE *fdopen_tempfile(struct tempfile *tempfile, const char *mode)
{
	if (!is_tempfile_active(tempfile))
		BUG("fdopen_tempfile() called for inactive object");
	if (tempfile->fp)
		BUG("fdopen_tempfile() called for open object");

	tempfile->fp = fdopen(tempfile->fd, mode);
	return tempfile->fp;
}