#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  InitRL; int /*<<< orphan*/  RunLength; TYPE_2__* FoundState; TYPE_1__* MinContext; } ;
struct TYPE_8__ {int Freq; } ;
struct TYPE_7__ {int SummFreq; } ;
typedef  TYPE_3__ CPpmd7 ;

/* Variables and functions */
 int MAX_FREQ ; 
 int /*<<< orphan*/  Rescale (TYPE_3__*) ; 
 int /*<<< orphan*/  UpdateModel (TYPE_3__*) ; 

__attribute__((used)) static void Ppmd7_Update2(CPpmd7 *p)
{
  p->MinContext->SummFreq += 4;
  if ((p->FoundState->Freq += 4) > MAX_FREQ)
    Rescale(p);
  p->RunLength = p->InitRL;
  UpdateModel(p);
}