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
struct physical {int /*<<< orphan*/  fd; TYPE_1__* handler; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* read ) (struct physical*,void*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LogPHYSICAL ; 
 int /*<<< orphan*/  log_DumpBuff (int /*<<< orphan*/ ,char*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  stub1 (struct physical*,void*,size_t) ; 

ssize_t
physical_Read(struct physical *p, void *buf, size_t nbytes)
{
  ssize_t ret;

  if (p->handler && p->handler->read)
    ret = (*p->handler->read)(p, buf, nbytes);
  else
    ret = read(p->fd, buf, nbytes);

  log_DumpBuff(LogPHYSICAL, "read", buf, ret);

  return ret;
}