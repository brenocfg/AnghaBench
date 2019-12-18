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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int check_file_status (struct pt_section*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int pt_sec_file_map (struct pt_section*,int /*<<< orphan*/ *) ; 
 int pt_sec_posix_map (struct pt_section*,int) ; 
 int pt_sec_posix_map_success (struct pt_section*) ; 
 int pt_section_lock (struct pt_section*) ; 
 int /*<<< orphan*/  pt_section_unlock (struct pt_section*) ; 
 int pte_bad_file ; 
 int pte_internal ; 

int pt_section_map(struct pt_section *section)
{
	const char *filename;
	FILE *file;
	int fd, errcode;

	if (!section)
		return -pte_internal;

	errcode = pt_section_lock(section);
	if (errcode < 0)
		return errcode;

	if (section->mcount)
		return pt_sec_posix_map_success(section);

	if (section->mapping)
		goto out_unlock;

	filename = section->filename;
	if (!filename)
		goto out_unlock;

	errcode = -pte_bad_file;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		goto out_unlock;

	errcode = check_file_status(section, fd);
	if (errcode < 0)
		goto out_fd;

	/* We close the file on success.  This does not unmap the section. */
	errcode = pt_sec_posix_map(section, fd);
	if (!errcode) {
		close(fd);

		return pt_sec_posix_map_success(section);
	}

	/* Fall back to file based sections - report the original error
	 * if we fail to convert the file descriptor.
	 */
	file = fdopen(fd, "rb");
	if (!file) {
		errcode = -pte_bad_file;
		goto out_fd;
	}

	/* We need to keep the file open on success.  It will be closed when
	 * the section is unmapped.
	 */
	errcode = pt_sec_file_map(section, file);
	if (!errcode)
		return pt_sec_posix_map_success(section);

	fclose(file);
	goto out_unlock;

out_fd:
	close(fd);

out_unlock:
	(void) pt_section_unlock(section);
	return errcode;
}