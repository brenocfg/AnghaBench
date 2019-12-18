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
struct TYPE_4__ {long m_resident; char* comm; long majflt; long minflt; long m_size; long nice; long nlwp; long pgrp; long pid; long ppid; long priority; long processor; long session; long starttime_ctime; long st_uid; long time; long tgid; long tpgid; long tty_nr; char* user; int /*<<< orphan*/  state; int /*<<< orphan*/  percent_cpu; TYPE_1__* settings; } ;
struct TYPE_3__ {int direction; int sortKey; } ;
typedef  TYPE_1__ Settings ;
typedef  TYPE_2__ Process ;

/* Variables and functions */
#define  COMM 150 
#define  MAJFLT 149 
#define  MINFLT 148 
#define  M_RESIDENT 147 
#define  M_SIZE 146 
#define  NICE 145 
#define  NLWP 144 
#define  PERCENT_CPU 143 
#define  PERCENT_MEM 142 
#define  PGRP 141 
#define  PID 140 
#define  PPID 139 
#define  PRIORITY 138 
#define  PROCESSOR 137 
 long Process_sortState (int /*<<< orphan*/ ) ; 
#define  SESSION 136 
#define  STARTTIME 135 
#define  STATE 134 
#define  ST_UID 133 
#define  TGID 132 
#define  TIME 131 
#define  TPGID 130 
#define  TTY_NR 129 
#define  USER 128 
 long strcmp (char*,char*) ; 

long Process_compare(const void* v1, const void* v2) {
   Process *p1, *p2;
   Settings *settings = ((Process*)v1)->settings;
   if (settings->direction == 1) {
      p1 = (Process*)v1;
      p2 = (Process*)v2;
   } else {
      p2 = (Process*)v1;
      p1 = (Process*)v2;
   }
   switch (settings->sortKey) {
   case PERCENT_CPU:
      return (p2->percent_cpu > p1->percent_cpu ? 1 : -1);
   case PERCENT_MEM:
      return (p2->m_resident - p1->m_resident);
   case COMM:
      return strcmp(p1->comm, p2->comm);
   case MAJFLT:
      return (p2->majflt - p1->majflt);
   case MINFLT:
      return (p2->minflt - p1->minflt);
   case M_RESIDENT:
      return (p2->m_resident - p1->m_resident);
   case M_SIZE:
      return (p2->m_size - p1->m_size);
   case NICE:
      return (p1->nice - p2->nice);
   case NLWP:
      return (p1->nlwp - p2->nlwp);
   case PGRP:
      return (p1->pgrp - p2->pgrp);
   case PID:
      return (p1->pid - p2->pid);
   case PPID:
      return (p1->ppid - p2->ppid);
   case PRIORITY:
      return (p1->priority - p2->priority);
   case PROCESSOR:
      return (p1->processor - p2->processor);
   case SESSION:
      return (p1->session - p2->session);
   case STARTTIME: {
      if (p1->starttime_ctime == p2->starttime_ctime)
         return (p1->pid - p2->pid);
      else
         return (p1->starttime_ctime - p2->starttime_ctime);
   }
   case STATE:
      return (Process_sortState(p1->state) - Process_sortState(p2->state));
   case ST_UID:
      return (p1->st_uid - p2->st_uid);
   case TIME:
      return ((p2->time) - (p1->time));
   case TGID:
      return (p1->tgid - p2->tgid);
   case TPGID:
      return (p1->tpgid - p2->tpgid);
   case TTY_NR:
      return (p1->tty_nr - p2->tty_nr);
   case USER:
      return strcmp(p1->user ? p1->user : "", p2->user ? p2->user : "");
   default:
      return (p1->pid - p2->pid);
   }
}