#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt32 ;
struct TYPE_2__ {int Code; int Low; int Range; } ;
typedef  TYPE_1__ CPpmd7z_RangeDec ;

/* Variables and functions */

__attribute__((used)) static UInt32 Range_GetThreshold(void *pp, UInt32 total)
{
  CPpmd7z_RangeDec *p = (CPpmd7z_RangeDec *)pp;
  return (p->Code - p->Low) / (p->Range /= total);
}