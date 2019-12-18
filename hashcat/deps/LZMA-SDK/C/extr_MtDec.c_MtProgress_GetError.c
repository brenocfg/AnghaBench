#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cs; int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ CMtProgress ;

/* Variables and functions */
 int /*<<< orphan*/  CriticalSection_Enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CriticalSection_Leave (int /*<<< orphan*/ *) ; 

SRes MtProgress_GetError(CMtProgress *p)
{
  SRes res;
  CriticalSection_Enter(&p->cs);
  res = p->res;
  CriticalSection_Leave(&p->cs);
  return res;
}