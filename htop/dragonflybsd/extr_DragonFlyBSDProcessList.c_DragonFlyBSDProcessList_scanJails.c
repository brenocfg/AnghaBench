#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ jails; } ;
typedef  TYPE_1__ DragonFlyBSDProcessList ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  Hashtable_delete (scalar_t__) ; 
 scalar_t__ Hashtable_get (scalar_t__,int) ; 
 scalar_t__ Hashtable_new (int,int) ; 
 int /*<<< orphan*/  Hashtable_put (scalar_t__,int,char*) ; 
 int atoi (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 char* strtok (char*,char*) ; 
 int sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* xMalloc (size_t) ; 
 char* xStrdup (char*) ; 

__attribute__((used)) static inline void DragonFlyBSDProcessList_scanJails(DragonFlyBSDProcessList* dfpl) {
   size_t len;
   char *jls; /* Jail list */
   char *curpos;
   char *nextpos;

   if (sysctlbyname("jail.list", NULL, &len, NULL, 0) == -1) {
      fprintf(stderr, "initial sysctlbyname / jail.list failed\n");
      exit(3);
   }
retry:
   if (len == 0)
      return;

   jls = xMalloc(len);
   if (jls == NULL) {
      fprintf(stderr, "xMalloc failed\n");
      exit(4);
   }
   if (sysctlbyname("jail.list", jls, &len, NULL, 0) == -1) {
      if (errno == ENOMEM) {
         free(jls);
         goto retry;
      }
      fprintf(stderr, "sysctlbyname / jail.list failed\n");
      exit(5);
   }

   if (dfpl->jails) {
      Hashtable_delete(dfpl->jails);
   }
   dfpl->jails = Hashtable_new(20, true);
   curpos = jls;
   while (curpos) {
      int jailid;
      char *str_hostname;
      nextpos = strchr(curpos, '\n');
      if (nextpos)
         *nextpos++ = 0;

      jailid = atoi(strtok(curpos, " "));
      str_hostname = strtok(NULL, " ");

      char *jname = (char *) (Hashtable_get(dfpl->jails, jailid));
      if (jname == NULL) {
         jname = xStrdup(str_hostname);
         Hashtable_put(dfpl->jails, jailid, jname);
      }

      curpos = nextpos;
  }
  free(jls);
}