#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {long pid; } ;
struct TYPE_9__ {long m_drs; long m_dt; long m_lrs; long m_trs; long m_share; long long utime; long long cutime; long long stime; long long cstime; long starttime; long long io_rchar; long long io_wchar; long long io_syscr; long long io_syscw; long long io_read_bytes; long long io_write_bytes; long long io_cancelled_write_bytes; long long io_rate_read_bps; long long io_rate_write_bps; long ctid; long vpid; long vxid; char* cgroup; long oom; int /*<<< orphan*/  swapin_delay_percent; int /*<<< orphan*/  blkio_delay_percent; int /*<<< orphan*/  cpu_delay_percent; TYPE_1__ super; } ;
struct TYPE_8__ {TYPE_2__* settings; } ;
struct TYPE_7__ {int direction; scalar_t__ sortKey; } ;
typedef  TYPE_2__ Settings ;
typedef  TYPE_3__ Process ;
typedef  TYPE_4__ LinuxProcess ;

/* Variables and functions */
#define  CGROUP 156 
#define  CNCLWB 155 
#define  CSTIME 154 
#define  CTID 153 
#define  CUTIME 152 
#define  IO_PRIORITY 151 
#define  IO_RATE 150 
#define  IO_READ_RATE 149 
#define  IO_WRITE_RATE 148 
 long LinuxProcess_effectiveIOPriority (TYPE_4__*) ; 
#define  M_DRS 147 
#define  M_DT 146 
#define  M_LRS 145 
#define  M_SHARE 144 
#define  M_TRS 143 
#define  OOM 142 
#define  PERCENT_CPU_DELAY 141 
#define  PERCENT_IO_DELAY 140 
#define  PERCENT_SWAP_DELAY 139 
 long Process_compare (void const*,void const*) ; 
#define  RBYTES 138 
#define  RCHAR 137 
#define  STARTTIME 136 
#define  STIME 135 
#define  SYSCR 134 
#define  SYSCW 133 
#define  UTIME 132 
#define  VPID 131 
#define  VXID 130 
#define  WBYTES 129 
#define  WCHAR 128 
 long strcmp (char*,char*) ; 

long LinuxProcess_compare(const void* v1, const void* v2) {
   LinuxProcess *p1, *p2;
   Settings *settings = ((Process*)v1)->settings;
   if (settings->direction == 1) {
      p1 = (LinuxProcess*)v1;
      p2 = (LinuxProcess*)v2;
   } else {
      p2 = (LinuxProcess*)v1;
      p1 = (LinuxProcess*)v2;
   }
   long long diff;
   switch ((int)settings->sortKey) {
   case M_DRS:
      return (p2->m_drs - p1->m_drs);
   case M_DT:
      return (p2->m_dt - p1->m_dt);
   case M_LRS:
      return (p2->m_lrs - p1->m_lrs);
   case M_TRS:
      return (p2->m_trs - p1->m_trs);
   case M_SHARE:
      return (p2->m_share - p1->m_share);
   case UTIME:  diff = p2->utime - p1->utime; goto test_diff;
   case CUTIME: diff = p2->cutime - p1->cutime; goto test_diff;
   case STIME:  diff = p2->stime - p1->stime; goto test_diff;
   case CSTIME: diff = p2->cstime - p1->cstime; goto test_diff;
   case STARTTIME: {
      if (p1->starttime == p2->starttime)
         return (p1->super.pid - p2->super.pid);
      else
         return (p1->starttime - p2->starttime);
   }
   #ifdef HAVE_TASKSTATS
   case RCHAR:  diff = p2->io_rchar - p1->io_rchar; goto test_diff;
   case WCHAR:  diff = p2->io_wchar - p1->io_wchar; goto test_diff;
   case SYSCR:  diff = p2->io_syscr - p1->io_syscr; goto test_diff;
   case SYSCW:  diff = p2->io_syscw - p1->io_syscw; goto test_diff;
   case RBYTES: diff = p2->io_read_bytes - p1->io_read_bytes; goto test_diff;
   case WBYTES: diff = p2->io_write_bytes - p1->io_write_bytes; goto test_diff;
   case CNCLWB: diff = p2->io_cancelled_write_bytes - p1->io_cancelled_write_bytes; goto test_diff;
   case IO_READ_RATE:  diff = p2->io_rate_read_bps - p1->io_rate_read_bps; goto test_diff;
   case IO_WRITE_RATE: diff = p2->io_rate_write_bps - p1->io_rate_write_bps; goto test_diff;
   case IO_RATE: diff = (p2->io_rate_read_bps + p2->io_rate_write_bps) - (p1->io_rate_read_bps + p1->io_rate_write_bps); goto test_diff;
   #endif
   #ifdef HAVE_OPENVZ
   case CTID:
      return (p2->ctid - p1->ctid);
   case VPID:
      return (p2->vpid - p1->vpid);
   #endif
   #ifdef HAVE_VSERVER
   case VXID:
      return (p2->vxid - p1->vxid);
   #endif
   #ifdef HAVE_CGROUP
   case CGROUP:
      return strcmp(p1->cgroup ? p1->cgroup : "", p2->cgroup ? p2->cgroup : "");
   #endif
   case OOM:
      return (p2->oom - p1->oom);
   #ifdef HAVE_DELAYACCT
   case PERCENT_CPU_DELAY:
      return (p2->cpu_delay_percent > p1->cpu_delay_percent ? 1 : -1);
   case PERCENT_IO_DELAY:
      return (p2->blkio_delay_percent > p1->blkio_delay_percent ? 1 : -1);
   case PERCENT_SWAP_DELAY:
      return (p2->swapin_delay_percent > p1->swapin_delay_percent ? 1 : -1);
   #endif
   case IO_PRIORITY:
      return LinuxProcess_effectiveIOPriority(p1) - LinuxProcess_effectiveIOPriority(p2);
   default:
      return Process_compare(v1, v2);
   }
   test_diff:
   return (diff > 0) ? 1 : (diff < 0 ? -1 : 0);
}