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

/* Variables and functions */
 int /*<<< orphan*/  AT_REMOVEDIR ; 
 int CAP_ACCEPT ; 
 int CAP_ACL_CHECK ; 
 int CAP_ACL_DELETE ; 
 int CAP_ACL_GET ; 
 int CAP_ACL_SET ; 
 int CAP_BIND ; 
 int CAP_CONNECT ; 
 int CAP_CREATE ; 
 int CAP_EVENT ; 
 int CAP_EXTATTR_DELETE ; 
 int CAP_EXTATTR_GET ; 
 int CAP_EXTATTR_LIST ; 
 int CAP_EXTATTR_SET ; 
 int CAP_FCHDIR ; 
 int CAP_FCHFLAGS ; 
 int CAP_FCHMOD ; 
 int CAP_FCHOWN ; 
 int CAP_FCNTL ; 
 int CAP_FEXECVE ; 
 int CAP_FLOCK ; 
 int CAP_FPATHCONF ; 
 int CAP_FSCK ; 
 int CAP_FSTAT ; 
 int CAP_FSTATFS ; 
 int CAP_FSYNC ; 
 int CAP_FTRUNCATE ; 
 int CAP_FUTIMES ; 
 int CAP_GETPEERNAME ; 
 int CAP_GETSOCKNAME ; 
 int CAP_GETSOCKOPT ; 
 int CAP_IOCTL ; 
 int CAP_LINKAT ; 
 int CAP_LISTEN ; 
 int CAP_LOOKUP ; 
 int CAP_MAC_GET ; 
 int CAP_MAC_SET ; 
 int CAP_MKDIRAT ; 
 int CAP_MKFIFOAT ; 
 int CAP_MKNODAT ; 
 int CAP_MMAP ; 
 int CAP_MMAP_R ; 
 int CAP_MMAP_RW ; 
 int CAP_MMAP_RWX ; 
 int CAP_MMAP_RX ; 
 int CAP_MMAP_W ; 
 int CAP_MMAP_WX ; 
 int CAP_MMAP_X ; 
 int CAP_PDGETPID ; 
 int CAP_PDKILL ; 
 int CAP_PDWAIT ; 
 int CAP_PEELOFF ; 
 int CAP_POST_EVENT ; 
 int CAP_PREAD ; 
 int CAP_PWRITE ; 
 int CAP_READ ; 
 int CAP_RECV ; 
 int CAP_RENAMEAT ; 
 int CAP_SEEK ; 
 int CAP_SEM_GETVALUE ; 
 int CAP_SEM_POST ; 
 int CAP_SEM_WAIT ; 
 int CAP_SEND ; 
 int CAP_SETSOCKOPT ; 
 int CAP_SHUTDOWN ; 
 int CAP_SYMLINKAT ; 
 int CAP_TTYHOOK ; 
 int CAP_UNLINKAT ; 
 int CAP_WRITE ; 
 int /*<<< orphan*/  KEEP_ERRNO (int /*<<< orphan*/ ) ; 
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 int PASSED ; 
 int /*<<< orphan*/  TRY (int) ; 
 int cap_enter () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/ * mkdtemp (char*) ; 
 int mkstemp (char*) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  rmdir (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  unlinkat (int,char*,int /*<<< orphan*/ ) ; 

int
test_capabilities(void)
{
	int filefd, dirfd, tmpfd;
	int success = PASSED;
	char file[] = "/tmp/cap_test.XXXXXXXXXX";
	char dir[] = "/tmp/cap_test.XXXXXXXXXX";

	filefd = mkstemp(file);
	if (filefd < 0)
		err(-1, "mkstemp");
	if (mkdtemp(dir) == NULL) {
		KEEP_ERRNO(unlink(file));
		err(-1, "mkdtemp");
	}
	dirfd = open(dir, O_RDONLY | O_DIRECTORY);
	if (dirfd == -1) {
		KEEP_ERRNO(unlink(file));
		KEEP_ERRNO(rmdir(dir));
		err(-1, "open");
	}
	tmpfd = open("/tmp", O_RDONLY | O_DIRECTORY);
	if (tmpfd == -1) {
		KEEP_ERRNO(unlink(file));
		KEEP_ERRNO(rmdir(dir));
		err(-1, "open");
	}

	if (cap_enter() == -1) {
		KEEP_ERRNO(unlink(file));
		KEEP_ERRNO(rmdir(dir));
		err(-1, "cap_enter");
	}

	TRY(CAP_READ);
	TRY(CAP_WRITE);
	TRY(CAP_SEEK);
	TRY(CAP_PREAD);
	TRY(CAP_PWRITE);
	TRY(CAP_READ | CAP_WRITE);
	TRY(CAP_PREAD | CAP_PWRITE);
	TRY(CAP_MMAP);
	TRY(CAP_MMAP_R);
	TRY(CAP_MMAP_W);
	TRY(CAP_MMAP_X);
	TRY(CAP_MMAP_RW);
	TRY(CAP_MMAP_RX);
	TRY(CAP_MMAP_WX);
	TRY(CAP_MMAP_RWX);
	TRY(CAP_CREATE | CAP_READ | CAP_LOOKUP);
	TRY(CAP_CREATE | CAP_WRITE | CAP_LOOKUP);
	TRY(CAP_CREATE | CAP_READ | CAP_WRITE | CAP_LOOKUP);
#ifdef TODO
	TRY(CAP_FEXECVE);
#endif
	TRY(CAP_FSYNC);
	TRY(CAP_FSYNC | CAP_READ | CAP_LOOKUP);
	TRY(CAP_FSYNC | CAP_WRITE | CAP_LOOKUP);
	TRY(CAP_FSYNC | CAP_READ | CAP_WRITE | CAP_LOOKUP);
	TRY(CAP_FTRUNCATE);
	TRY(CAP_FTRUNCATE | CAP_READ | CAP_LOOKUP);
	TRY(CAP_FTRUNCATE | CAP_WRITE | CAP_LOOKUP);
	TRY(CAP_FTRUNCATE | CAP_READ | CAP_WRITE | CAP_LOOKUP);
#ifdef TODO
	TRY(CAP_FCHDIR);
#endif
	TRY(CAP_FCHFLAGS);
	TRY(CAP_FCHOWN);
	TRY(CAP_FCHOWN | CAP_LOOKUP);
	TRY(CAP_FCHMOD | CAP_LOOKUP);
	TRY(CAP_FCNTL);
#ifdef TODO
	TRY(CAP_FLOCK);
#endif
	TRY(CAP_FPATHCONF);
#ifdef TODO
	TRY(CAP_FSCK);
#endif
	TRY(CAP_FSTAT | CAP_LOOKUP);
	TRY(CAP_FSTATFS);
	TRY(CAP_FUTIMES | CAP_LOOKUP);
	TRY(CAP_LINKAT | CAP_LOOKUP);
	TRY(CAP_MKDIRAT | CAP_LOOKUP);
	TRY(CAP_MKFIFOAT | CAP_LOOKUP);
	TRY(CAP_MKNODAT | CAP_LOOKUP);
	TRY(CAP_SYMLINKAT | CAP_LOOKUP);
	TRY(CAP_UNLINKAT | CAP_LOOKUP);
	/* Rename needs CAP_RENAMEAT on source directory and CAP_LINKAT on destination directory. */
	TRY(CAP_RENAMEAT | CAP_UNLINKAT | CAP_LOOKUP);
#ifdef TODO
	TRY(CAP_LOOKUP);
	TRY(CAP_EXTATTR_DELETE);
	TRY(CAP_EXTATTR_GET);
	TRY(CAP_EXTATTR_LIST);
	TRY(CAP_EXTATTR_SET);
	TRY(CAP_ACL_CHECK);
	TRY(CAP_ACL_DELETE);
	TRY(CAP_ACL_GET);
	TRY(CAP_ACL_SET);
	TRY(CAP_ACCEPT);
	TRY(CAP_BIND);
	TRY(CAP_CONNECT);
	TRY(CAP_GETPEERNAME);
	TRY(CAP_GETSOCKNAME);
	TRY(CAP_GETSOCKOPT);
	TRY(CAP_LISTEN);
	TRY(CAP_PEELOFF);
	TRY(CAP_RECV);
	TRY(CAP_SEND);
	TRY(CAP_SETSOCKOPT);
	TRY(CAP_SHUTDOWN);
	TRY(CAP_MAC_GET);
	TRY(CAP_MAC_SET);
	TRY(CAP_SEM_GETVALUE);
	TRY(CAP_SEM_POST);
	TRY(CAP_SEM_WAIT);
	TRY(CAP_POST_EVENT);
	TRY(CAP_EVENT);
	TRY(CAP_IOCTL);
	TRY(CAP_TTYHOOK);
	TRY(CAP_PDGETPID);
	TRY(CAP_PDWAIT);
	TRY(CAP_PDKILL);
#endif

	(void)unlinkat(tmpfd, file + strlen("/tmp/"), 0);
	(void)unlinkat(tmpfd, dir + strlen("/tmp/"), AT_REMOVEDIR);

	return (success);
}