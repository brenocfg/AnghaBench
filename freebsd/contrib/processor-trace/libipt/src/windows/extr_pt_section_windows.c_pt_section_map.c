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
struct pt_section {char* filename; scalar_t__ mapping; scalar_t__ mcount; } ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  _O_RDONLY ; 
 int /*<<< orphan*/  _close (int) ; 
 int /*<<< orphan*/ * _fdopen (int,char*) ; 
 int _open_osfhandle (intptr_t,int /*<<< orphan*/ ) ; 
 int check_file_status (struct pt_section*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int pt_sec_file_map (struct pt_section*,int /*<<< orphan*/ *) ; 
 int pt_sec_windows_map (struct pt_section*,int) ; 
 int pt_sec_windows_map_success (struct pt_section*) ; 
 int pt_section_lock (struct pt_section*) ; 
 int /*<<< orphan*/  pt_section_unlock (struct pt_section*) ; 
 int pte_bad_file ; 
 int pte_internal ; 

int pt_section_map(struct pt_section *section)
{
	const char *filename;
	HANDLE fh;
	FILE *file;
	int fd, errcode;

	if (!section)
		return -pte_internal;

	errcode = pt_section_lock(section);
	if (errcode < 0)
		return errcode;

	if (section->mcount)
		return pt_sec_windows_map_success(section);

	if (section->mapping) {
		errcode = -pte_internal;
		goto out_unlock;
	}

	filename = section->filename;
	if (!filename) {
		errcode = -pte_internal;
		goto out_unlock;
	}

	fh = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, NULL,
			 OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fh == INVALID_HANDLE_VALUE) {
		/* We failed to open the file read-only.  Let's try to open it
		 * read-write; maybe our user has the file open for writing.
		 *
		 * We will detect changes to the file via fstat().
		 */

		fh = CreateFileA(filename, GENERIC_READ, FILE_SHARE_WRITE,
				 NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
				 NULL);
		if (fh == INVALID_HANDLE_VALUE) {
			errcode = -pte_bad_file;
			goto out_unlock;
		}
	}

	fd = _open_osfhandle((intptr_t) fh, _O_RDONLY);
	if (fd == -1) {
		errcode = -pte_bad_file;
		goto out_fh;
	}

	errcode = check_file_status(section, fd);
	if (errcode < 0)
		goto out_fd;

	/* We leave the file open on success.  It will be closed when the
	 * section is unmapped.
	 */
	errcode = pt_sec_windows_map(section, fd);
	if (!errcode)
		return pt_sec_windows_map_success(section);

	/* Fall back to file based sections - report the original error
	 * if we fail to convert the file descriptor.
	 */
	file = _fdopen(fd, "rb");
	if (!file) {
		errcode = -pte_bad_file;
		goto out_fd;
	}

	/* We need to keep the file open on success.  It will be closed when
	 * the section is unmapped.
	 */
	errcode = pt_sec_file_map(section, file);
	if (!errcode)
		return pt_sec_windows_map_success(section);

	fclose(file);
	goto out_unlock;

out_fd:
	_close(fd);
	return errcode;

out_fh:
	CloseHandle(fh);

out_unlock:
	(void) pt_section_unlock(section);
	return errcode;
}