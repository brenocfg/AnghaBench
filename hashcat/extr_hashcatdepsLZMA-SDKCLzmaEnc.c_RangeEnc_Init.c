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
struct TYPE_3__ {int range; int /*<<< orphan*/  res; scalar_t__ processed; int /*<<< orphan*/  bufBase; int /*<<< orphan*/  buf; scalar_t__ cacheSize; scalar_t__ low; scalar_t__ cache; } ;
typedef  TYPE_1__ CRangeEnc ;

/* Variables and functions */
 int /*<<< orphan*/  SZ_OK ; 

__attribute__((used)) static void RangeEnc_Init(CRangeEnc *p)
{
  /* Stream.Init(); */
  p->range = 0xFFFFFFFF;
  p->cache = 0;
  p->low = 0;
  p->cacheSize = 0;

  p->buf = p->bufBase;

  p->processed = 0;
  p->res = SZ_OK;
}