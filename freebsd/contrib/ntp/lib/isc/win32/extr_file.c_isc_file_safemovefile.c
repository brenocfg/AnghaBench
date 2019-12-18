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
struct stat {int dummy; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ DeleteFile (char*) ; 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  ENOENT ; 
 scalar_t__ FALSE ; 
 scalar_t__ MoveFile (char const*,char const*) ; 
 scalar_t__ TRUE ; 
 int _S_IREAD ; 
 int _S_IWRITE ; 
 int /*<<< orphan*/  _chmod (char const*,int) ; 
 int /*<<< orphan*/  _close (int) ; 
 int /*<<< orphan*/  errno ; 
 int mkstemp (char*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

int
isc_file_safemovefile(const char *oldname, const char *newname) {
	BOOL filestatus;
	char buf[512];
	struct stat sbuf;
	BOOL exists = FALSE;
	int tmpfd;

	/*
	 * Make sure we have something to do
	 */
	if (stat(oldname, &sbuf) != 0) {
		errno = ENOENT;
		return (-1);
	}

	/*
	 * Rename to a backup the new file if it still exists
	 */
	if (stat(newname, &sbuf) == 0) {
		exists = TRUE;
		strcpy(buf, newname);
		strcat(buf, ".XXXXX");
		tmpfd = mkstemp(buf);
		if (tmpfd > 0)
			_close(tmpfd);
		DeleteFile(buf);
		_chmod(newname, _S_IREAD | _S_IWRITE);

		filestatus = MoveFile(newname, buf);
	}
	/* Now rename the file to the new name
	 */
	_chmod(oldname, _S_IREAD | _S_IWRITE);

	filestatus = MoveFile(oldname, newname);
	if (filestatus == 0) {
		/*
		 * Try to rename the backup back to the original name
		 * if the backup got created
		 */
		if (exists == TRUE) {
			filestatus = MoveFile(buf, newname);
			if (filestatus == 0)
				errno = EACCES;
		}
		return (-1);
	}

	/*
	 * Delete the backup file if it got created
	 */
	if (exists == TRUE)
		filestatus = DeleteFile(buf);
	return (0);
}