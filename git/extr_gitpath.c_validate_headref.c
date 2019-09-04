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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct object_id {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  get_oid_hex (char*,struct object_id*) ; 
 scalar_t__ isspace (char const) ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read_in_full (int,char*,int) ; 
 int readlink (char const*,char*,int) ; 
 scalar_t__ skip_prefix (char*,char*,char const**) ; 
 scalar_t__ starts_with (char const*,char*) ; 

int validate_headref(const char *path)
{
	struct stat st;
	char buffer[256];
	const char *refname;
	struct object_id oid;
	int fd;
	ssize_t len;

	if (lstat(path, &st) < 0)
		return -1;

	/* Make sure it is a "refs/.." symlink */
	if (S_ISLNK(st.st_mode)) {
		len = readlink(path, buffer, sizeof(buffer)-1);
		if (len >= 5 && !memcmp("refs/", buffer, 5))
			return 0;
		return -1;
	}

	/*
	 * Anything else, just open it and try to see if it is a symbolic ref.
	 */
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return -1;
	len = read_in_full(fd, buffer, sizeof(buffer)-1);
	close(fd);

	if (len < 0)
		return -1;
	buffer[len] = '\0';

	/*
	 * Is it a symbolic ref?
	 */
	if (skip_prefix(buffer, "ref:", &refname)) {
		while (isspace(*refname))
			refname++;
		if (starts_with(refname, "refs/"))
			return 0;
	}

	/*
	 * Is this a detached HEAD?
	 */
	if (!get_oid_hex(buffer, &oid))
		return 0;

	return -1;
}