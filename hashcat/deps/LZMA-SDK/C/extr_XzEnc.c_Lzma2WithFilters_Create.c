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
struct TYPE_3__ {scalar_t__ lzma2; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  TYPE_1__ CLzma2WithFilters ;

/* Variables and functions */
 scalar_t__ Lzma2Enc_Create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_ERROR_MEM ; 
 int /*<<< orphan*/  SZ_OK ; 

__attribute__((used)) static SRes Lzma2WithFilters_Create(CLzma2WithFilters *p, ISzAllocPtr alloc, ISzAllocPtr bigAlloc)
{
  if (!p->lzma2)
  {
    p->lzma2 = Lzma2Enc_Create(alloc, bigAlloc);
    if (!p->lzma2)
      return SZ_ERROR_MEM;
  }
  return SZ_OK;
}