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
struct TYPE_3__ {void** high; void** low; } ;
typedef  TYPE_1__ CLenEnc ;

/* Variables and functions */
 int LZMA_NUM_PB_STATES_MAX ; 
 unsigned int kLenNumHighSymbols ; 
 int kLenNumLowBits ; 
 void* kProbInitValue ; 

__attribute__((used)) static void LenEnc_Init(CLenEnc *p)
{
  unsigned i;
  for (i = 0; i < (LZMA_NUM_PB_STATES_MAX << (kLenNumLowBits + 1)); i++)
    p->low[i] = kProbInitValue;
  for (i = 0; i < kLenNumHighSymbols; i++)
    p->high[i] = kProbInitValue;
}