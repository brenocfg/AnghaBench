#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_4__ {void* m_resident; void* m_size; } ;
struct TYPE_5__ {void* m_dt; void* m_drs; void* m_lrs; void* m_trs; void* m_share; TYPE_1__ super; } ;
typedef  TYPE_2__ LinuxProcess ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_NAME ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROC_LINE_LENGTH ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 void* strtol (char*,char**,int) ; 
 int /*<<< orphan*/  xSnprintf (char*,int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int xread (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool LinuxProcessList_readStatmFile(LinuxProcess* process, const char* dirname, const char* name) {
   char filename[MAX_NAME+1];
   xSnprintf(filename, MAX_NAME, "%s/%s/statm", dirname, name);
   int fd = open(filename, O_RDONLY);
   if (fd == -1)
      return false;
   char buf[PROC_LINE_LENGTH + 1];
   ssize_t rres = xread(fd, buf, PROC_LINE_LENGTH);
   close(fd);
   if (rres < 1) return false;

   char *p = buf;
   errno = 0;
   process->super.m_size = strtol(p, &p, 10); if (*p == ' ') p++;
   process->super.m_resident = strtol(p, &p, 10); if (*p == ' ') p++;
   process->m_share = strtol(p, &p, 10); if (*p == ' ') p++;
   process->m_trs = strtol(p, &p, 10); if (*p == ' ') p++;
   process->m_lrs = strtol(p, &p, 10); if (*p == ' ') p++;
   process->m_drs = strtol(p, &p, 10); if (*p == ' ') p++;
   process->m_dt = strtol(p, &p, 10);
   return (errno == 0);
}