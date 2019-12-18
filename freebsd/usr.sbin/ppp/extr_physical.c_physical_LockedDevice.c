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
struct TYPE_2__ {char* full; char const* base; } ;
struct physical {scalar_t__ fd; scalar_t__ type; TYPE_1__ name; } ;

/* Variables and functions */
 scalar_t__ PHYS_DIRECT ; 

const char *
physical_LockedDevice(struct physical *p)
{
  if (p->fd >= 0 && *p->name.full == '/' && p->type != PHYS_DIRECT)
    return p->name.base;

  return NULL;
}