#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* settings; } ;
struct TYPE_5__ {int direction; scalar_t__ sortKey; } ;
struct TYPE_4__ {long zoneid; long projid; long taskid; long poolid; long contid; char* zname; long realpid; long realppid; long lwpid; } ;
typedef  TYPE_1__ SolarisProcess ;
typedef  TYPE_2__ Settings ;
typedef  TYPE_3__ Process ;

/* Variables and functions */
#define  CONTID 136 
#define  LWPID 135 
#define  PID 134 
#define  POOLID 133 
#define  PPID 132 
#define  PROJID 131 
 long Process_compare (void const*,void const*) ; 
#define  TASKID 130 
#define  ZONE 129 
#define  ZONEID 128 
 long strcmp (char*,char*) ; 

long SolarisProcess_compare(const void* v1, const void* v2) {
   SolarisProcess *p1, *p2;
   Settings* settings = ((Process*)v1)->settings;
   if (settings->direction == 1) {
      p1 = (SolarisProcess*)v1;
      p2 = (SolarisProcess*)v2;
   } else {
      p2 = (SolarisProcess*)v1;
      p1 = (SolarisProcess*)v2;
   }
   switch ((int) settings->sortKey) {
   case ZONEID:
      return (p1->zoneid - p2->zoneid);
   case PROJID:
      return (p1->projid - p2->projid);
   case TASKID:
      return (p1->taskid - p2->taskid);
   case POOLID:
      return (p1->poolid - p2->poolid);
   case CONTID:
      return (p1->contid - p2->contid);
   case ZONE:
      return strcmp(p1->zname ? p1->zname : "global", p2->zname ? p2->zname : "global");
   case PID:
      return (p1->realpid - p2->realpid);
   case PPID:
      return (p1->realppid - p2->realppid);
   case LWPID:
      return (p1->lwpid - p2->lwpid);
   default:
      return Process_compare(v1, v2);
   }
}