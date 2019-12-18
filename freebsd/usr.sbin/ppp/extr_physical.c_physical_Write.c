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
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (struct physical*,void const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LogPHYSICAL ; 
 int /*<<< orphan*/  log_DumpBuff (int /*<<< orphan*/ ,char*,void const*,size_t) ; 
 int /*<<< orphan*/  stub1 (struct physical*,void const*,size_t) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,void const*,size_t) ; 

ssize_t
physical_Write(struct physical *p, const void *buf, size_t nbytes)
{
  log_DumpBuff(LogPHYSICAL, "write", buf, nbytes);

  if (p->handler && p->handler->write)
    return (*p->handler->write)(p, buf, nbytes);

  return write(p->fd, buf, nbytes);
}