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
struct TYPE_3__ {size_t size; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_1__ CBuf ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ ISzAlloc_Alloc (int /*<<< orphan*/ ,size_t) ; 

int Buf_Create(CBuf *p, size_t size, ISzAllocPtr alloc)
{
  p->size = 0;
  if (size == 0)
  {
    p->data = 0;
    return 1;
  }
  p->data = (Byte *)ISzAlloc_Alloc(alloc, size);
  if (p->data)
  {
    p->size = size;
    return 1;
  }
  return 0;
}