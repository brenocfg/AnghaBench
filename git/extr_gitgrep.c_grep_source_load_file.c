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
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
struct grep_source {char* identifier; char* buf; size_t size; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error_errno (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ read_in_full (int,char*,size_t) ; 
 char* xmallocz (size_t) ; 
 size_t xsize_t (scalar_t__) ; 

__attribute__((used)) static int grep_source_load_file(struct grep_source *gs)
{
	const char *filename = gs->identifier;
	struct stat st;
	char *data;
	size_t size;
	int i;

	if (lstat(filename, &st) < 0) {
	err_ret:
		if (errno != ENOENT)
			error_errno(_("failed to stat '%s'"), filename);
		return -1;
	}
	if (!S_ISREG(st.st_mode))
		return -1;
	size = xsize_t(st.st_size);
	i = open(filename, O_RDONLY);
	if (i < 0)
		goto err_ret;
	data = xmallocz(size);
	if (st.st_size != read_in_full(i, data, size)) {
		error_errno(_("'%s': short read"), filename);
		close(i);
		free(data);
		return -1;
	}
	close(i);

	gs->buf = data;
	gs->size = size;
	return 0;
}