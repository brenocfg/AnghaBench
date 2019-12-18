#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
struct es_passwd {TYPE_2__* ufld; TYPE_1__* uflg; } ;
struct TYPE_4__ {scalar_t__ fd_uid; int /*<<< orphan*/  fd_name; } ;
struct TYPE_3__ {int /*<<< orphan*/  fg_uid; } ;

/* Variables and functions */
 int LOG_AUTHPRIV ; 
 int LOG_NOTICE ; 
 struct es_passwd* getespwuid (int /*<<< orphan*/ ) ; 
 scalar_t__ getluid () ; 
 scalar_t__ getprogname () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  set_auth_parameters (int,char**) ; 
 int /*<<< orphan*/  setluid (scalar_t__) ; 
 int /*<<< orphan*/  syslog (int,char*,int /*<<< orphan*/ ,...) ; 

int
do_osfc2_magic(uid_t uid)
{
#ifdef HAVE_OSFC2
    struct es_passwd *epw;
    char *argv[2];

    /* fake */
    argv[0] = (char*)getprogname();
    argv[1] = NULL;
    set_auth_parameters(1, argv);

    epw = getespwuid(uid);
    if(epw == NULL) {
	syslog(LOG_AUTHPRIV|LOG_NOTICE,
	       "getespwuid failed for %d", uid);
	printf("Sorry.\n");
	return 1;
    }
    /* We don't check for auto-retired, foo-retired,
       bar-retired, or any other kind of retired accounts
       here; neither do we check for time-locked accounts, or
       any other kind of serious C2 mumbo-jumbo. We do,
       however, call setluid, since failing to do so is not
       very good (take my word for it). */

    if(!epw->uflg->fg_uid) {
	syslog(LOG_AUTHPRIV|LOG_NOTICE,
	       "attempted login by %s (has no uid)", epw->ufld->fd_name);
	printf("Sorry.\n");
	return 1;
    }
    setluid(epw->ufld->fd_uid);
    if(getluid() != epw->ufld->fd_uid) {
	syslog(LOG_AUTHPRIV|LOG_NOTICE,
	       "failed to set LUID for %s (%d)",
	       epw->ufld->fd_name, epw->ufld->fd_uid);
	printf("Sorry.\n");
	return 1;
    }
#endif /* HAVE_OSFC2 */
    return 0;
}