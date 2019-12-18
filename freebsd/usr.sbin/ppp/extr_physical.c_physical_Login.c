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
struct utmpx {int /*<<< orphan*/  ut_host; int /*<<< orphan*/  ut_line; int /*<<< orphan*/  ut_user; int /*<<< orphan*/  ut_id; int /*<<< orphan*/  ut_tv; int /*<<< orphan*/  ut_type; } ;
struct TYPE_4__ {char const* base; } ;
struct physical {scalar_t__ type; int Utmp; TYPE_2__ name; TYPE_1__* handler; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ID0login (struct utmpx*) ; 
 scalar_t__ PHYS_DIRECT ; 
 scalar_t__ TCP_DEVICE ; 
 scalar_t__ UDP_DEVICE ; 
 int /*<<< orphan*/  USER_PROCESS ; 
 char* getenv (char*) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* memchr (int /*<<< orphan*/ ,char,int) ; 
 int /*<<< orphan*/  memset (struct utmpx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

void
physical_Login(struct physical *p, const char *name)
{
  if (p->type == PHYS_DIRECT && *p->name.base && !p->Utmp) {
    struct utmpx ut;
    const char *connstr;
    char *colon;

    memset(&ut, 0, sizeof ut);
    ut.ut_type = USER_PROCESS;
    gettimeofday(&ut.ut_tv, NULL);
    snprintf(ut.ut_id, sizeof ut.ut_id, "%xppp", (int)getpid());
    strncpy(ut.ut_user, name, sizeof ut.ut_user);
    if (p->handler && (p->handler->type == TCP_DEVICE ||
                       p->handler->type == UDP_DEVICE)) {
      strncpy(ut.ut_host, p->name.base, sizeof ut.ut_host);
      colon = memchr(ut.ut_host, ':', sizeof ut.ut_host);
      if (colon)
        *colon = '\0';
    } else
      strncpy(ut.ut_line, p->name.base, sizeof ut.ut_line);
    if ((connstr = getenv("CONNECT")))
      /* mgetty sets this to the connection speed */
      strncpy(ut.ut_host, connstr, sizeof ut.ut_host);
    ID0login(&ut);
    p->Utmp = 1;
  }
}