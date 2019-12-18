#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_7__ {int highlightMegabytes; int direction; int /*<<< orphan*/  treeView; int /*<<< orphan*/  highlightThreads; } ;
struct TYPE_6__ {double percent_cpu; double percent_mem; int indent; int m_resident; int m_size; int priority; scalar_t__ st_uid; int /*<<< orphan*/  user; int /*<<< orphan*/  tty_nr; int /*<<< orphan*/  tpgid; int /*<<< orphan*/  tgid; int /*<<< orphan*/  time; int /*<<< orphan*/  state; int /*<<< orphan*/  starttime_show; int /*<<< orphan*/  session; int /*<<< orphan*/  processor; TYPE_2__* settings; int /*<<< orphan*/  ppid; int /*<<< orphan*/  pid; int /*<<< orphan*/  pgrp; int /*<<< orphan*/  nlwp; int /*<<< orphan*/  nice; int /*<<< orphan*/  minflt; int /*<<< orphan*/  majflt; int /*<<< orphan*/  showChildren; } ;
typedef  int /*<<< orphan*/  RichString ;
typedef  int ProcessField ;
typedef  TYPE_1__ Process ;

/* Variables and functions */
#define  COMM 150 
 int* CRT_colors ; 
 char** CRT_treeStr ; 
 size_t DEFAULT_COLOR ; 
#define  MAJFLT 149 
#define  MINFLT 148 
#define  M_RESIDENT 147 
#define  M_SIZE 146 
#define  NICE 145 
#define  NLWP 144 
 int PAGE_SIZE_KB ; 
#define  PERCENT_CPU 143 
#define  PERCENT_MEM 142 
#define  PGRP 141 
#define  PID 140 
#define  PPID 139 
#define  PRIORITY 138 
#define  PROCESSOR 137 
 size_t PROCESS_BASENAME ; 
 size_t PROCESS_D_STATE ; 
 size_t PROCESS_HIGH_PRIORITY ; 
 size_t PROCESS_LOW_PRIORITY ; 
 size_t PROCESS_R_STATE ; 
 size_t PROCESS_SHADOW ; 
 size_t PROCESS_THREAD ; 
 size_t PROCESS_THREAD_BASENAME ; 
 size_t PROCESS_TREE ; 
 int /*<<< orphan*/  Process_colorNumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int Process_getuid ; 
 int /*<<< orphan*/  Process_humanNumber (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  Process_isThread (TYPE_1__*) ; 
 int /*<<< orphan*/  Process_pidFormat ; 
 int /*<<< orphan*/  Process_printTime (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Process_writeCommand (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RichString_append (int /*<<< orphan*/ *,int,char*) ; 
#define  SESSION 136 
#define  STARTTIME 135 
#define  STATE 134 
#define  ST_UID 133 
 int /*<<< orphan*/  Settings_cpuId (TYPE_2__*,int /*<<< orphan*/ ) ; 
#define  TGID 132 
#define  TIME 131 
#define  TPGID 130 
 size_t TREE_STR_BEND ; 
 size_t TREE_STR_OPEN ; 
 size_t TREE_STR_RTEE ; 
 size_t TREE_STR_SHUT ; 
 size_t TREE_STR_TEND ; 
 size_t TREE_STR_VERT ; 
#define  TTY_NR 129 
#define  USER 128 
 int /*<<< orphan*/  major (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minor (int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  xSnprintf (char*,int,char*,...) ; 

void Process_writeField(Process* this, RichString* str, ProcessField field) {
   char buffer[256]; buffer[255] = '\0';
   int attr = CRT_colors[DEFAULT_COLOR];
   int baseattr = CRT_colors[PROCESS_BASENAME];
   int n = sizeof(buffer) - 1;
   bool coloring = this->settings->highlightMegabytes;

   switch (field) {
   case PERCENT_CPU: {
      if (this->percent_cpu > 999.9) {
         xSnprintf(buffer, n, "%4u ", (unsigned int)this->percent_cpu); 
      } else if (this->percent_cpu > 99.9) {
         xSnprintf(buffer, n, "%3u. ", (unsigned int)this->percent_cpu); 
      } else {
         xSnprintf(buffer, n, "%4.1f ", this->percent_cpu);
      }
      break;
   }
   case PERCENT_MEM: {
      if (this->percent_mem > 99.9) {
         xSnprintf(buffer, n, "100. "); 
      } else {
         xSnprintf(buffer, n, "%4.1f ", this->percent_mem);
      }
      break;
   }
   case COMM: {
      if (this->settings->highlightThreads && Process_isThread(this)) {
         attr = CRT_colors[PROCESS_THREAD];
         baseattr = CRT_colors[PROCESS_THREAD_BASENAME];
      }
      if (!this->settings->treeView || this->indent == 0) {
         Process_writeCommand(this, attr, baseattr, str);
         return;
      } else {
         char* buf = buffer;
         int maxIndent = 0;
         bool lastItem = (this->indent < 0);
         int indent = (this->indent < 0 ? -this->indent : this->indent);

         for (int i = 0; i < 32; i++)
            if (indent & (1U << i))
               maxIndent = i+1;
          for (int i = 0; i < maxIndent - 1; i++) {
            int written, ret;
            if (indent & (1 << i))
               ret = snprintf(buf, n, "%s  ", CRT_treeStr[TREE_STR_VERT]);
            else
               ret = snprintf(buf, n, "   ");
            if (ret < 0 || ret >= n) {
               written = n;
            } else {
               written = ret;
            }
            buf += written;
            n -= written;
         }
         const char* draw = CRT_treeStr[lastItem ? (this->settings->direction == 1 ? TREE_STR_BEND : TREE_STR_TEND) : TREE_STR_RTEE];
         xSnprintf(buf, n, "%s%s ", draw, this->showChildren ? CRT_treeStr[TREE_STR_SHUT] : CRT_treeStr[TREE_STR_OPEN] );
         RichString_append(str, CRT_colors[PROCESS_TREE], buffer);
         Process_writeCommand(this, attr, baseattr, str);
         return;
      }
   }
   case MAJFLT: Process_colorNumber(str, this->majflt, coloring); return;
   case MINFLT: Process_colorNumber(str, this->minflt, coloring); return;
   case M_RESIDENT: Process_humanNumber(str, this->m_resident * PAGE_SIZE_KB, coloring); return;
   case M_SIZE: Process_humanNumber(str, this->m_size * PAGE_SIZE_KB, coloring); return;
   case NICE: {
      xSnprintf(buffer, n, "%3ld ", this->nice);
      attr = this->nice < 0 ? CRT_colors[PROCESS_HIGH_PRIORITY]
           : this->nice > 0 ? CRT_colors[PROCESS_LOW_PRIORITY]
           : attr;
      break;
   }
   case NLWP: xSnprintf(buffer, n, "%4ld ", this->nlwp); break;
   case PGRP: xSnprintf(buffer, n, Process_pidFormat, this->pgrp); break;
   case PID: xSnprintf(buffer, n, Process_pidFormat, this->pid); break;
   case PPID: xSnprintf(buffer, n, Process_pidFormat, this->ppid); break;
   case PRIORITY: {
      if(this->priority <= -100)
         xSnprintf(buffer, n, " RT ");
      else
         xSnprintf(buffer, n, "%3ld ", this->priority);
      break;
   }
   case PROCESSOR: xSnprintf(buffer, n, "%3d ", Settings_cpuId(this->settings, this->processor)); break;
   case SESSION: xSnprintf(buffer, n, Process_pidFormat, this->session); break;
   case STARTTIME: xSnprintf(buffer, n, "%s", this->starttime_show); break;
   case STATE: {
      xSnprintf(buffer, n, "%c ", this->state);
      switch(this->state) {
          case 'R':
              attr = CRT_colors[PROCESS_R_STATE];
              break;
          case 'D':
              attr = CRT_colors[PROCESS_D_STATE];
              break;
      }
      break;
   }
   case ST_UID: xSnprintf(buffer, n, "%4d ", this->st_uid); break;
   case TIME: Process_printTime(str, this->time); return;
   case TGID: xSnprintf(buffer, n, Process_pidFormat, this->tgid); break;
   case TPGID: xSnprintf(buffer, n, Process_pidFormat, this->tpgid); break;
   case TTY_NR: xSnprintf(buffer, n, "%3u:%3u ", major(this->tty_nr), minor(this->tty_nr)); break;
   case USER: {
      if (Process_getuid != (int) this->st_uid)
         attr = CRT_colors[PROCESS_SHADOW];
      if (this->user) {
         xSnprintf(buffer, n, "%-9s ", this->user);
      } else {
         xSnprintf(buffer, n, "%-9d ", this->st_uid);
      }
      if (buffer[9] != '\0') {
         buffer[9] = ' ';
         buffer[10] = '\0';
      }
      break;
   }
   default:
      xSnprintf(buffer, n, "- ");
   }
   RichString_append(str, attr, buffer);
}