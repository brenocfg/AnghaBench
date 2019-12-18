#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  command ;
struct TYPE_6__ {int isKernelThread; } ;
struct TYPE_5__ {int basenameOffset; } ;
typedef  TYPE_1__ Process ;
typedef  TYPE_2__ LinuxProcess ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_NAME ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setCommand (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  xSnprintf (char*,int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int xread (int,char*,int) ; 

__attribute__((used)) static bool LinuxProcessList_readCmdlineFile(Process* process, const char* dirname, const char* name) {
   char filename[MAX_NAME+1];
   xSnprintf(filename, MAX_NAME, "%s/%s/cmdline", dirname, name);
   int fd = open(filename, O_RDONLY);
   if (fd == -1)
      return false;
         
   char command[4096+1]; // max cmdline length on Linux
   int amtRead = xread(fd, command, sizeof(command) - 1);
   close(fd);
   int tokenEnd = 0; 
   int lastChar = 0;
   if (amtRead == 0) {
      ((LinuxProcess*)process)->isKernelThread = true;
      return true;
   } else if (amtRead < 0) {
      return false;
   }
   for (int i = 0; i < amtRead; i++) {
      if (command[i] == '\0' || command[i] == '\n') {
         if (tokenEnd == 0) {
            tokenEnd = i;
         }
         command[i] = ' ';
      } else {
         lastChar = i;
      }
   }
   if (tokenEnd == 0) {
      tokenEnd = amtRead;
   }
   command[lastChar + 1] = '\0';
   process->basenameOffset = tokenEnd;
   setCommand(process, command, lastChar + 1);

   return true;
}