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
struct fifolog_file {int fd; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIFOLOG_FILE_MAGIC ; 
 int errno ; 
 int /*<<< orphan*/  fifolog_int_close (struct fifolog_file**) ; 
 char* fifolog_int_open_i (struct fifolog_file*,char const*,int) ; 
 struct fifolog_file* malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct fifolog_file*,struct fifolog_file*,int) ; 
 int /*<<< orphan*/  memset (struct fifolog_file*,int /*<<< orphan*/ ,int) ; 

const char *
fifolog_int_open(struct fifolog_file **ff, const char *fname, int mode)
{
	struct fifolog_file fs, *f;
	const char *retval;
	int e;

	f = &fs;
	memset(f, 0, sizeof *f);
	f->fd = -1;
	retval = fifolog_int_open_i(f, fname, mode);
	e = errno;
	if (retval == NULL) {
		*ff = malloc(sizeof *f);
		if (*ff != NULL) {
			memcpy(*ff, f, sizeof *f);
			(*ff)->magic = FIFOLOG_FILE_MAGIC;
			return (retval);
		}
	}
	fifolog_int_close(&f);
	errno = e;
	return (retval);
}