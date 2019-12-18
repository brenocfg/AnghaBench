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
struct TYPE_3__ {size_t size; size_t pos; int /*<<< orphan*/  const* data; } ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_1__ CDynBuf ;
typedef  int /*<<< orphan*/  const Byte ;

/* Variables and functions */
 scalar_t__ ISzAlloc_Alloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ISzAlloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

int DynBuf_Write(CDynBuf *p, const Byte *buf, size_t size, ISzAllocPtr alloc)
{
  if (size > p->size - p->pos)
  {
    size_t newSize = p->pos + size;
    Byte *data;
    newSize += newSize / 4;
    data = (Byte *)ISzAlloc_Alloc(alloc, newSize);
    if (!data)
      return 0;
    p->size = newSize;
    if (p->pos != 0)
      memcpy(data, p->data, p->pos);
    ISzAlloc_Free(alloc, p->data);
    p->data = data;
  }
  if (size != 0)
  {
    memcpy(p->data + p->pos, buf, size);
    p->pos += size;
  }
  return 1;
}