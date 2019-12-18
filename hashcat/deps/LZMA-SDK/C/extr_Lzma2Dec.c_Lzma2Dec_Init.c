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
struct TYPE_3__ {int needInitLevel; int /*<<< orphan*/  decoder; scalar_t__ unpackSize; int /*<<< orphan*/  isExtraMode; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ CLzma2Dec ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  LZMA2_STATE_CONTROL ; 
 int /*<<< orphan*/  LzmaDec_Init (int /*<<< orphan*/ *) ; 

void Lzma2Dec_Init(CLzma2Dec *p)
{
  p->state = LZMA2_STATE_CONTROL;
  p->needInitLevel = 0xE0;
  p->isExtraMode = False;
  p->unpackSize = 0;
  
  // p->decoder.dicPos = 0; // we can use it instead of full init
  LzmaDec_Init(&p->decoder);
}