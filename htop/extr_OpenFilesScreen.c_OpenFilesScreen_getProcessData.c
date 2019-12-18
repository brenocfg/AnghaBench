#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int pid_t ;
struct TYPE_7__ {int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {TYPE_3__ data; struct TYPE_6__* next; } ;
struct TYPE_5__ {int error; TYPE_2__* files; TYPE_3__ data; } ;
typedef  TYPE_1__ OpenFiles_ProcessData ;
typedef  TYPE_2__ OpenFiles_FileData ;
typedef  TYPE_3__ OpenFiles_Data ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 char* String_readLine (int /*<<< orphan*/ *) ; 
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execlp (char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int fork () ; 
 int /*<<< orphan*/  free (char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int pipe (int*) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 
 void* xCalloc (int,int) ; 
 int /*<<< orphan*/  xSnprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  xStrdup (char*) ; 

__attribute__((used)) static OpenFiles_ProcessData* OpenFilesScreen_getProcessData(pid_t pid) {
   char buffer[1025];
   xSnprintf(buffer, 1024, "%d", pid);
   OpenFiles_ProcessData* pdata = xCalloc(1, sizeof(OpenFiles_ProcessData));
   OpenFiles_FileData* fdata = NULL;
   OpenFiles_Data* item = &(pdata->data);
   int fdpair[2];
   if (pipe(fdpair) == -1) {
      pdata->error = 1;
      return pdata;
   }
   pid_t child = fork();
   if (child == -1) {
      pdata->error = 1;
      return pdata;
   }
   if (child == 0) {
      close(fdpair[0]);
      dup2(fdpair[1], STDOUT_FILENO);
      close(fdpair[1]);
      int fdnull = open("/dev/null", O_WRONLY);
      if (fdnull < 0)
         exit(1);
      dup2(fdnull, STDERR_FILENO);
      close(fdnull);
      execlp("lsof", "lsof", "-P", "-p", buffer, "-F", NULL);
      exit(127);
   }
   close(fdpair[1]);
   FILE* fd = fdopen(fdpair[0], "r");
   for (;;) {
      char* line = String_readLine(fd);
      if (!line) {
         break;
      }
      unsigned char cmd = line[0];
      if (cmd == 'f') {
         OpenFiles_FileData* nextFile = xCalloc(1, sizeof(OpenFiles_FileData));
         if (fdata == NULL) {
            pdata->files = nextFile;
         } else {
            fdata->next = nextFile;
         }
         fdata = nextFile;
         item = &(fdata->data);
      }
      item->data[cmd] = xStrdup(line + 1);
      free(line);
   }
   int wstatus;
   if (waitpid(child, &wstatus, 0) == -1) {
      pdata->error = 1;
      return pdata;
   }
   if (!WIFEXITED(wstatus))
      pdata->error = 1;
   else
      pdata->error = WEXITSTATUS(wstatus);
   return pdata;
}