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
typedef  scalar_t__ UInt64 ;
struct TYPE_3__ {int /*<<< orphan*/  check; scalar_t__ realStreamFinished; scalar_t__ processed; scalar_t__ limit; } ;
typedef  scalar_t__ Int64 ;
typedef  TYPE_1__ CSeqCheckInStream ;

/* Variables and functions */
 int /*<<< orphan*/  XzCheck_Init (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void SeqCheckInStream_Init(CSeqCheckInStream *p, unsigned checkMode)
{
  p->limit = (UInt64)(Int64)-1;
  p->processed = 0;
  p->realStreamFinished = 0;
  XzCheck_Init(&p->check, checkMode);
}