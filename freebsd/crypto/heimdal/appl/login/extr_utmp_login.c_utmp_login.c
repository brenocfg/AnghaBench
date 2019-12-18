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
struct utmp {int dummy; } ;

/* Variables and functions */
 int O_APPEND ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  _PATH_UTMP ; 
 int /*<<< orphan*/  _PATH_WTMP ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  endutent () ; 
 int /*<<< orphan*/  lseek (int,long,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_utmp (struct utmp*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  pututline (struct utmp*) ; 
 int /*<<< orphan*/  setutent () ; 
 int ttyslot () ; 
 int /*<<< orphan*/  utmpname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int,struct utmp*,int) ; 

void utmp_login(char *tty, const char *username, const char *hostname)
{
    struct utmp utmp;
    int fd;

    prepare_utmp (&utmp, tty, username, hostname);

#ifdef HAVE_SETUTENT
    utmpname(_PATH_UTMP);
    setutent();
    pututline(&utmp);
    endutent();
#else

#ifdef HAVE_TTYSLOT
    {
      int ttyno;
      ttyno = ttyslot();
      if (ttyno > 0 && (fd = open(_PATH_UTMP, O_WRONLY, 0)) >= 0) {
	lseek(fd, (long)(ttyno * sizeof(struct utmp)), SEEK_SET);
	write(fd, &utmp, sizeof(struct utmp));
	close(fd);
      }
    }
#endif /* HAVE_TTYSLOT */
#endif /* HAVE_SETUTENT */

    if ((fd = open(_PATH_WTMP, O_WRONLY|O_APPEND, 0)) >= 0) {
	write(fd, &utmp, sizeof(struct utmp));
	close(fd);
    }
}