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
struct kinfo_proc {char ki_jid; } ;
struct iovec {char* iov_base; int iov_len; } ;
typedef  int /*<<< orphan*/  jnamebuf ;

/* Variables and functions */
 int JAIL_ERRMSGLEN ; 
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  errno ; 
 char* jail_errmsg ; 
 int jail_get (struct iovec*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror_r (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xSnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 char* xStrdup (char*) ; 

char* FreeBSDProcessList_readJailName(struct kinfo_proc* kproc) {
   int    jid;
   struct iovec jiov[6];
   char*  jname;
   char   jnamebuf[MAXHOSTNAMELEN];

   if (kproc->ki_jid != 0 ){
      memset(jnamebuf, 0, sizeof(jnamebuf));
      *(const void **)&jiov[0].iov_base = "jid";
      jiov[0].iov_len = sizeof("jid");
      jiov[1].iov_base = &kproc->ki_jid;
      jiov[1].iov_len = sizeof(kproc->ki_jid);
      *(const void **)&jiov[2].iov_base = "name";
      jiov[2].iov_len = sizeof("name");
      jiov[3].iov_base = jnamebuf;
      jiov[3].iov_len = sizeof(jnamebuf);
      *(const void **)&jiov[4].iov_base = "errmsg";
      jiov[4].iov_len = sizeof("errmsg");
      jiov[5].iov_base = jail_errmsg;
      jiov[5].iov_len = JAIL_ERRMSGLEN;
      jail_errmsg[0] = 0;
      jid = jail_get(jiov, 6, 0);
      if (jid < 0) {
         if (!jail_errmsg[0])
            xSnprintf(jail_errmsg, JAIL_ERRMSGLEN, "jail_get: %s", strerror(errno));
            return NULL;
      } else if (jid == kproc->ki_jid) {
         jname = xStrdup(jnamebuf);
         if (jname == NULL)
            strerror_r(errno, jail_errmsg, JAIL_ERRMSGLEN);
         return jname;
      } else {
         return NULL;
      }
   } else {
      jnamebuf[0]='-';
      jnamebuf[1]='\0';
      jname = xStrdup(jnamebuf);
   }
   return jname;
}