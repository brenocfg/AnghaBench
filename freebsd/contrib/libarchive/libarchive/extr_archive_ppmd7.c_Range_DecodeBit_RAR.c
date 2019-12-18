#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UInt32 ;
struct TYPE_6__ {scalar_t__ (* GetThreshold ) (TYPE_2__*,scalar_t__) ;int /*<<< orphan*/  (* Decode ) (TYPE_2__*,scalar_t__,scalar_t__) ;} ;
struct TYPE_7__ {TYPE_1__ p; } ;
typedef  TYPE_2__ CPpmd7z_RangeDec ;

/* Variables and functions */
 scalar_t__ PPMD_BIN_SCALE ; 
 scalar_t__ stub1 (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static UInt32 Range_DecodeBit_RAR(void *pp, UInt32 size0)
{
  CPpmd7z_RangeDec *p = (CPpmd7z_RangeDec *)pp;
  UInt32 bit, value = p->p.GetThreshold(p, PPMD_BIN_SCALE);
  if(value < size0)
  {
    bit = 0;
    p->p.Decode(p, 0, size0);
  }
  else
  {
    bit = 1;
    p->p.Decode(p, size0, PPMD_BIN_SCALE - size0);
  }
  return bit;
}