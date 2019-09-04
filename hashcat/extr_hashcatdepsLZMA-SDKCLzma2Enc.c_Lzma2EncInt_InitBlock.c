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
struct TYPE_3__ {void* needInitProp; void* needInitState; scalar_t__ srcPos; } ;
typedef  TYPE_1__ CLzma2EncInt ;

/* Variables and functions */
 void* True ; 

__attribute__((used)) static void Lzma2EncInt_InitBlock(CLzma2EncInt *p)
{
  p->srcPos = 0;
  p->needInitState = True;
  p->needInitProp = True;
}