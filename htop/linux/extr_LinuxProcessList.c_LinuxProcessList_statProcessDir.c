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
struct stat {int /*<<< orphan*/  st_uid; } ;
struct TYPE_3__ {int /*<<< orphan*/  st_uid; } ;
typedef  TYPE_1__ Process ;

/* Variables and functions */
 int MAX_NAME ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  xSnprintf (char*,int,char*,char const*,char*) ; 

__attribute__((used)) static bool LinuxProcessList_statProcessDir(Process* process, const char* dirname, char* name) {
   char filename[MAX_NAME+1];
   filename[MAX_NAME] = '\0';

   xSnprintf(filename, MAX_NAME, "%s/%s", dirname, name);
   struct stat sstat;
   int statok = stat(filename, &sstat);
   if (statok == -1)
      return false;
   process->st_uid = sstat.st_uid;
   return true;
}