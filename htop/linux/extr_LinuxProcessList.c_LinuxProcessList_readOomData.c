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
struct TYPE_3__ {unsigned int oom; } ;
typedef  TYPE_1__ LinuxProcess ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_NAME ; 
 int /*<<< orphan*/  PROC_LINE_LENGTH ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int sscanf (char*,char*,unsigned int*) ; 
 int /*<<< orphan*/  xSnprintf (char*,int /*<<< orphan*/ ,char*,char const*,char const*) ; 

__attribute__((used)) static void LinuxProcessList_readOomData(LinuxProcess* process, const char* dirname, const char* name) {
   char filename[MAX_NAME+1];
   xSnprintf(filename, MAX_NAME, "%s/%s/oom_score", dirname, name);
   FILE* file = fopen(filename, "r");
   if (!file) {
      return;
   }
   char buffer[PROC_LINE_LENGTH + 1];
   if (fgets(buffer, PROC_LINE_LENGTH, file)) {
      unsigned int oom;
      int ok = sscanf(buffer, "%32u", &oom);
      if (ok >= 1) {
         process->oom = oom;
      }
   }
   fclose(file);
}