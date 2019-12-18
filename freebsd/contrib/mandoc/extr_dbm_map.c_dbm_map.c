#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int st_size; } ;

/* Variables and functions */
 int EFBIG ; 
 int EFTYPE ; 
 int INT32_MAX ; 
 long long MANDOCDB_MAGIC ; 
 long long MANDOCDB_VERSION ; 
 int /*<<< orphan*/  MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 long long be32toh (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dbm_base ; 
 int /*<<< orphan*/ * dbm_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  const* dbm_getint (int) ; 
 int errno ; 
 int fstat (int,TYPE_1__*) ; 
 int ifd ; 
 long long max_offset ; 
 int /*<<< orphan*/  mmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__ st ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  warnx (char*,char const*,...) ; 

int
dbm_map(const char *fname)
{
	int		 save_errno;
	const int32_t	*magic;

	if ((ifd = open(fname, O_RDONLY)) == -1)
		return -1;
	if (fstat(ifd, &st) == -1)
		goto fail;
	if (st.st_size < 5) {
		warnx("dbm_map(%s): File too short", fname);
		errno = EFTYPE;
		goto fail;
	}
	if (st.st_size > INT32_MAX) {
		errno = EFBIG;
		goto fail;
	}
	if ((dbm_base = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED,
	    ifd, 0)) == MAP_FAILED)
		goto fail;
	magic = dbm_getint(0);
	if (be32toh(*magic) != MANDOCDB_MAGIC) {
		if (strncmp(dbm_base, "SQLite format 3", 15))
			warnx("dbm_map(%s): "
			    "Bad initial magic %x (expected %x)",
			    fname, be32toh(*magic), MANDOCDB_MAGIC);
		else
			warnx("dbm_map(%s): "
			    "Obsolete format based on SQLite 3",
			    fname);
		errno = EFTYPE;
		goto fail;
	}
	magic = dbm_getint(1);
	if (be32toh(*magic) != MANDOCDB_VERSION) {
		warnx("dbm_map(%s): Bad version number %d (expected %d)",
		    fname, be32toh(*magic), MANDOCDB_VERSION);
		errno = EFTYPE;
		goto fail;
	}
	max_offset = be32toh(*dbm_getint(3)) + sizeof(int32_t);
	if (st.st_size != max_offset) {
		warnx("dbm_map(%s): Inconsistent file size %lld (expected %d)",
		    fname, (long long)st.st_size, max_offset);
		errno = EFTYPE;
		goto fail;
	}
	if ((magic = dbm_get(*dbm_getint(3))) == NULL) {
		errno = EFTYPE;
		goto fail;
	}
	if (be32toh(*magic) != MANDOCDB_MAGIC) {
		warnx("dbm_map(%s): Bad final magic %x (expected %x)",
		    fname, be32toh(*magic), MANDOCDB_MAGIC);
		errno = EFTYPE;
		goto fail;
	}
	return 0;

fail:
	save_errno = errno;
	close(ifd);
	errno = save_errno;
	return -1;
}