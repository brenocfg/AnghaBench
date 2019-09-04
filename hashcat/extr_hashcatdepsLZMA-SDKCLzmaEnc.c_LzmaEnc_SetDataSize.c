#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UInt64 ;
struct TYPE_3__ {int /*<<< orphan*/  expectedDataSize; } ;
struct TYPE_4__ {TYPE_1__ matchFinderBase; } ;
typedef  scalar_t__ CLzmaEncHandle ;
typedef  TYPE_2__ CLzmaEnc ;

/* Variables and functions */

void LzmaEnc_SetDataSize(CLzmaEncHandle pp, UInt64 expectedDataSiize)
{
  CLzmaEnc *p = (CLzmaEnc *)pp;
  p->matchFinderBase.expectedDataSize = expectedDataSiize;
}