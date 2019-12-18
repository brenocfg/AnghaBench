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
struct stat {size_t st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  UT_string ;

/* Variables and functions */
 unsigned char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int open (unsigned char const*,int /*<<< orphan*/ ) ; 
 int stat (unsigned char const*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucl_create_err (int /*<<< orphan*/ **,char*,unsigned char const*,int /*<<< orphan*/ ) ; 
 unsigned char* ucl_mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

bool
ucl_fetch_file (const unsigned char *filename, unsigned char **buf, size_t *buflen,
		UT_string **err, bool must_exist)
{
	int fd;
	struct stat st;

	if (stat (filename, &st) == -1 || !S_ISREG (st.st_mode)) {
		if (must_exist) {
			ucl_create_err (err, "cannot stat file %s: %s",
					filename, strerror (errno));
		}
		return false;
	}
	if (st.st_size == 0) {
		/* Do not map empty files */
		*buf = NULL;
		*buflen = 0;
	}
	else {
		if ((fd = open (filename, O_RDONLY)) == -1) {
			ucl_create_err (err, "cannot open file %s: %s",
					filename, strerror (errno));
			return false;
		}
		if ((*buf = ucl_mmap (NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED) {
			close (fd);
			ucl_create_err (err, "cannot mmap file %s: %s",
					filename, strerror (errno));
			*buf = NULL;

			return false;
		}
		*buflen = st.st_size;
		close (fd);
	}

	return true;
}