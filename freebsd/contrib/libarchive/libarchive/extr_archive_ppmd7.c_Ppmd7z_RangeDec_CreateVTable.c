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
struct TYPE_5__ {TYPE_1__ p; } ;
typedef  TYPE_2__ CPpmd7z_RangeDec ;

/* Variables and functions */
 int /*<<< orphan*/  Range_DecodeBit_7z ; 
 int /*<<< orphan*/  Range_Decode_7z ; 
 int /*<<< orphan*/  Range_GetThreshold ; 

__attribute__((used)) static void Ppmd7z_RangeDec_CreateVTable(CPpmd7z_RangeDec *p)
{
  p->p.GetThreshold = Range_GetThreshold;
  p->p.Decode = Range_Decode_7z;
  p->p.DecodeBit = Range_DecodeBit_7z;
}