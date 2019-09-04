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
struct TYPE_3__ {int /*<<< orphan*/ * blocks; scalar_t__ allocated; scalar_t__ size; scalar_t__ numBlocks; } ;
typedef  TYPE_1__ CXzEncIndex ;

/* Variables and functions */

__attribute__((used)) static void XzEncIndex_Construct(CXzEncIndex *p)
{
  p->numBlocks = 0;
  p->size = 0;
  p->allocated = 0;
  p->blocks = NULL;
}