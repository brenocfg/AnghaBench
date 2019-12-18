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
typedef  int /*<<< orphan*/  token_key ;
typedef  int /*<<< orphan*/  token_dir ;
typedef  int /*<<< orphan*/  key_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int /*<<< orphan*/ ) ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 int /*<<< orphan*/  atf_tc_fail (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ftok (char*,int) ; 
 char* mkdtemp (char*) ; 
 int open (char*,int,int) ; 
 int rmdir (char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int unlink (char*) ; 

key_t get_ftok(int id)
{
	int fd;
	char token_key[64], token_dir[64];
	char *tmpdir;
	key_t key;

	strlcpy(token_key, "/tmp/t_sysv.XXXXXX", sizeof(token_key));
	tmpdir = mkdtemp(token_key);
	ATF_REQUIRE_MSG(tmpdir != NULL, "mkdtemp() failed: %d", errno);

	strlcpy(token_dir, tmpdir, sizeof(token_dir));
	strlcpy(token_key, tmpdir, sizeof(token_key));
	strlcat(token_key, "/token_key", sizeof(token_key));

	/* Create the file, since ftok() requires it to exist! */

	fd = open(token_key, O_RDWR | O_CREAT | O_EXCL, 0600);
	if (fd == -1) {
		rmdir(tmpdir);
		atf_tc_fail("open() of temp file failed: %d", errno);
		return (key_t)-1;
	} else
		close(fd);

	key = ftok(token_key, id);

	ATF_REQUIRE_MSG(unlink(token_key) != -1, "unlink() failed: %d", errno);
	ATF_REQUIRE_MSG(rmdir(token_dir) != -1, "rmdir() failed: %d", errno);

	return key;
}