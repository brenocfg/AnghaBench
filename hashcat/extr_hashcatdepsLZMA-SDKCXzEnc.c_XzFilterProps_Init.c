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
struct TYPE_3__ {int /*<<< orphan*/  ipDefined; scalar_t__ ip; scalar_t__ delta; scalar_t__ id; } ;
typedef  TYPE_1__ CXzFilterProps ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 

void XzFilterProps_Init(CXzFilterProps *p)
{
  p->id = 0;
  p->delta = 0;
  p->ip = 0;
  p->ipDefined = False;
}