#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Read; } ;
struct TYPE_5__ {int /*<<< orphan*/ * p; } ;
struct TYPE_7__ {TYPE_2__ p; TYPE_1__ StateCoder; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_3__ CSeqInFilter ;

/* Variables and functions */
 int /*<<< orphan*/  SeqInFilter_Read ; 

__attribute__((used)) static void SeqInFilter_Construct(CSeqInFilter *p)
{
  p->buf = NULL;
  p->StateCoder.p = NULL;
  p->p.Read = SeqInFilter_Read;
}