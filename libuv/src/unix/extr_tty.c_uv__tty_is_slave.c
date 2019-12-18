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
struct stat {int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_mode; } ;
typedef  scalar_t__ devmajor_t ;

/* Variables and functions */
 scalar_t__ NODEVMAJOR ; 
 int /*<<< orphan*/  S_IFCHR ; 
 int /*<<< orphan*/  S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIOCGPTN ; 
 int /*<<< orphan*/  TIOCPTYGNAME ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ fstat (int const,struct stat*) ; 
 scalar_t__ getdevmajor (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int const,int /*<<< orphan*/ ,...) ; 
 scalar_t__ major (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ptsname (int const) ; 

__attribute__((used)) static int uv__tty_is_slave(const int fd) {
  int result;
#if defined(__linux__) || defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
  int dummy;

  result = ioctl(fd, TIOCGPTN, &dummy) != 0;
#elif defined(__APPLE__)
  char dummy[256];

  result = ioctl(fd, TIOCPTYGNAME, &dummy) != 0;
#elif defined(__NetBSD__)
  /*
   * NetBSD as an extension returns with ptsname(3) and ptsname_r(3) the slave
   * device name for both descriptors, the master one and slave one.
   *
   * Implement function to compare major device number with pts devices.
   *
   * The major numbers are machine-dependent, on NetBSD/amd64 they are
   * respectively:
   *  - master tty: ptc - major 6
   *  - slave tty:  pts - major 5
   */

  struct stat sb;
  /* Lookup device's major for the pts driver and cache it. */
  static devmajor_t pts = NODEVMAJOR;

  if (pts == NODEVMAJOR) {
    pts = getdevmajor("pts", S_IFCHR);
    if (pts == NODEVMAJOR)
      abort();
  }

  /* Lookup stat structure behind the file descriptor. */
  if (fstat(fd, &sb) != 0)
    abort();

  /* Assert character device. */
  if (!S_ISCHR(sb.st_mode))
    abort();

  /* Assert valid major. */
  if (major(sb.st_rdev) == NODEVMAJOR)
    abort();

  result = (pts == major(sb.st_rdev));
#else
  /* Fallback to ptsname
   */
  result = ptsname(fd) == NULL;
#endif
  return result;
}