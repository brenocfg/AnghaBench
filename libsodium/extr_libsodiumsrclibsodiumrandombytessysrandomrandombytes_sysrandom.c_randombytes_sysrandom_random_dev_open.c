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

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ EIO ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
randombytes_sysrandom_random_dev_open(void)
{
/* LCOV_EXCL_START */
    struct stat        st;
    static const char *devices[] = {
#  ifndef USE_BLOCKING_RANDOM
        "/dev/urandom",
#  endif
        "/dev/random", NULL
    };
    const char       **device = devices;
    int                fd;

#  ifdef BLOCK_ON_DEV_RANDOM
    if (randombytes_block_on_dev_random() != 0) {
        return -1;
    }
#  endif
    do {
        fd = open(*device, O_RDONLY);
        if (fd != -1) {
            if (fstat(fd, &st) == 0 &&
#  ifdef __COMPCERT__
                1
#  elif defined(S_ISNAM)
                (S_ISNAM(st.st_mode) || S_ISCHR(st.st_mode))
#  else
                S_ISCHR(st.st_mode)
#  endif
               ) {
#  if defined(F_SETFD) && defined(FD_CLOEXEC)
                (void) fcntl(fd, F_SETFD, fcntl(fd, F_GETFD) | FD_CLOEXEC);
#  endif
                return fd;
            }
            (void) close(fd);
        } else if (errno == EINTR) {
            continue;
        }
        device++;
    } while (*device != NULL);

    errno = EIO;
    return -1;
/* LCOV_EXCL_STOP */
}