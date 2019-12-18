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
typedef  int /*<<< orphan*/  UInt64 ;
struct TYPE_5__ {size_t numBlocks; TYPE_1__* blocks; } ;
struct TYPE_4__ {int /*<<< orphan*/  unpackSize; } ;
typedef  TYPE_2__ CXzStream ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_SIZE_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

UInt64 Xz_GetUnpackSize(const CXzStream *p)
{
  UInt64 size = 0;
  size_t i;
  for (i = 0; i < p->numBlocks; i++)
    ADD_SIZE_CHECK(size, p->blocks[i].unpackSize);
  return size;
}