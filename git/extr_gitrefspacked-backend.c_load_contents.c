#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_size; } ;
struct snapshot {int mmapped; int /*<<< orphan*/  buf; scalar_t__ eof; int /*<<< orphan*/  start; TYPE_1__* refs; int /*<<< orphan*/  validity; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 scalar_t__ MMAP_NONE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 size_t SMALL_FILE_SIZE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die_errno (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ mmap_strategy ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t read_in_full (int,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  stat_validity_update (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xmalloc (size_t) ; 
 int /*<<< orphan*/  xmmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 size_t xsize_t (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_contents(struct snapshot *snapshot)
{
	int fd;
	struct stat st;
	size_t size;
	ssize_t bytes_read;

	fd = open(snapshot->refs->path, O_RDONLY);
	if (fd < 0) {
		if (errno == ENOENT) {
			/*
			 * This is OK; it just means that no
			 * "packed-refs" file has been written yet,
			 * which is equivalent to it being empty,
			 * which is its state when initialized with
			 * zeros.
			 */
			return 0;
		} else {
			die_errno("couldn't read %s", snapshot->refs->path);
		}
	}

	stat_validity_update(&snapshot->validity, fd);

	if (fstat(fd, &st) < 0)
		die_errno("couldn't stat %s", snapshot->refs->path);
	size = xsize_t(st.st_size);

	if (!size) {
		close(fd);
		return 0;
	} else if (mmap_strategy == MMAP_NONE || size <= SMALL_FILE_SIZE) {
		snapshot->buf = xmalloc(size);
		bytes_read = read_in_full(fd, snapshot->buf, size);
		if (bytes_read < 0 || bytes_read != size)
			die_errno("couldn't read %s", snapshot->refs->path);
		snapshot->mmapped = 0;
	} else {
		snapshot->buf = xmmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
		snapshot->mmapped = 1;
	}
	close(fd);

	snapshot->start = snapshot->buf;
	snapshot->eof = snapshot->buf + size;

	return 1;
}