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
typedef  scalar_t__ v ;
typedef  int UInt32 ;
typedef  void* UInt16 ;
struct TYPE_3__ {void* SuccessorHigh; void* SuccessorLow; } ;
typedef  scalar_t__ CPpmd_Void_Ref ;
typedef  TYPE_1__ CPpmd_State ;

/* Variables and functions */

__attribute__((used)) static void SetSuccessor(CPpmd_State *p, CPpmd_Void_Ref v)
{
  (p)->SuccessorLow = (UInt16)((UInt32)(v) & 0xFFFF);
  (p)->SuccessorHigh = (UInt16)(((UInt32)(v) >> 16) & 0xFFFF);
}