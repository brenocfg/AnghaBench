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
struct thread_map {int thr_state; scalar_t__ thr_lwpp; } ;
struct thread_info {TYPE_1__* private; int /*<<< orphan*/  ptid; } ;
struct TYPE_5__ {int lwp_id; } ;
typedef  TYPE_2__ __lwp_desc_t ;
struct TYPE_4__ {int /*<<< orphan*/  mapp; int /*<<< orphan*/  stable; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  ISTID (int /*<<< orphan*/ ) ; 
#define  TS_FORK 133 
#define  TS_ONPROC 132 
#define  TS_RUNNABLE 131 
#define  TS_SLEEP 130 
#define  TS_SUSPENDED 129 
#define  TS_ZOMBIE 128 
 int /*<<< orphan*/  read_lwp (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  read_map (int /*<<< orphan*/ ,struct thread_map*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 

__attribute__((used)) static char *
uw_extra_thread_info (struct thread_info *info)
{
  static char buf[80];
  struct thread_map map;
  __lwp_desc_t lwp;
  int lwpid;
  char *name;

  if (!ISTID (info->ptid))
    return NULL;

  if (!info->private->stable)
    return "switching";

  if (!read_map (info->private->mapp, &map))
    return NULL;

  if (!map.thr_lwpp || !read_lwp ((CORE_ADDR)map.thr_lwpp, &lwp))
    lwpid = 0;
  else
    lwpid = lwp.lwp_id;

  switch (map.thr_state) {
  case TS_ONPROC:	name = "running";	break;
  case TS_SLEEP:	name = "sleeping";	break;
  case TS_RUNNABLE:	name = "runnable";	break;
  case TS_ZOMBIE:	name = "zombie";	break;
  case TS_SUSPENDED:	name = "suspended";	break;
#ifdef TS_FORK
  case TS_FORK:		name = "forking";	break;
#endif
  default:		name = "confused";	break;
  }

  if (!lwpid)
    return name;

  sprintf (buf, "%s, LWP %d", name, lwpid);
  return buf;
}