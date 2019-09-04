#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  DecodeBit; int /*<<< orphan*/  Decode; int /*<<< orphan*/  GetThreshold; } ;
struct TYPE_5__ {TYPE_1__ vt; } ;
typedef  TYPE_2__ CPpmd7z_RangeDec ;

/* Variables and functions */
 int /*<<< orphan*/  Range_Decode ; 
 int /*<<< orphan*/  Range_DecodeBit ; 
 int /*<<< orphan*/  Range_GetThreshold ; 

void Ppmd7z_RangeDec_CreateVTable(CPpmd7z_RangeDec *p)
{
  p->vt.GetThreshold = Range_GetThreshold;
  p->vt.Decode = Range_Decode;
  p->vt.DecodeBit = Range_DecodeBit;
}