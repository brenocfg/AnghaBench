#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {int /*<<< orphan*/  lwpid; int /*<<< orphan*/  realppid; int /*<<< orphan*/  realpid; int /*<<< orphan*/  zname; int /*<<< orphan*/  contid; int /*<<< orphan*/  poolid; int /*<<< orphan*/  taskid; int /*<<< orphan*/  projid; int /*<<< orphan*/  zoneid; } ;
typedef  TYPE_1__ SolarisProcess ;
typedef  int /*<<< orphan*/  RichString ;
typedef  scalar_t__ ProcessField ;
typedef  int /*<<< orphan*/  Process ;

/* Variables and functions */
#define  CONTID 136 
 int* CRT_colors ; 
 size_t DEFAULT_COLOR ; 
#define  LWPID 135 
#define  PID 134 
#define  POOLID 133 
#define  PPID 132 
#define  PROJID 131 
 int /*<<< orphan*/  Process_pidFormat ; 
 int /*<<< orphan*/  Process_writeField (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  RichString_append (int /*<<< orphan*/ *,int,char*) ; 
#define  TASKID 130 
#define  ZONE 129 
#define  ZONEID 128 
 int ZONENAME_MAX ; 
 int /*<<< orphan*/  xSnprintf (char*,int,char*,int,...) ; 

void SolarisProcess_writeField(Process* this, RichString* str, ProcessField field) {
   SolarisProcess* sp = (SolarisProcess*) this;
   char buffer[256]; buffer[255] = '\0';
   int attr = CRT_colors[DEFAULT_COLOR];
   int n = sizeof(buffer) - 1;
   switch ((int) field) {
   // add Solaris-specific fields here
   case ZONEID: xSnprintf(buffer, n, Process_pidFormat, sp->zoneid); break;
   case PROJID: xSnprintf(buffer, n, Process_pidFormat, sp->projid); break;
   case TASKID: xSnprintf(buffer, n, Process_pidFormat, sp->taskid); break;
   case POOLID: xSnprintf(buffer, n, Process_pidFormat, sp->poolid); break;
   case CONTID: xSnprintf(buffer, n, Process_pidFormat, sp->contid); break;
   case ZONE:{
      xSnprintf(buffer, n, "%-*s ", ZONENAME_MAX/4, sp->zname); break;
      if (buffer[ZONENAME_MAX/4] != '\0') {
         buffer[ZONENAME_MAX/4] = ' ';
         buffer[(ZONENAME_MAX/4)+1] = '\0';
      }
      break;
   }
   case PID: xSnprintf(buffer, n, Process_pidFormat, sp->realpid); break;
   case PPID: xSnprintf(buffer, n, Process_pidFormat, sp->realppid); break;
   case LWPID: xSnprintf(buffer, n, Process_pidFormat, sp->lwpid); break;
   default:
      Process_writeField(this, str, field);
      return;
   }
   RichString_append(str, attr, buffer);
}