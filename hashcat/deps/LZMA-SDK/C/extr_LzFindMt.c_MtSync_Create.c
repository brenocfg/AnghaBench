#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UInt32 ;
typedef  int /*<<< orphan*/  THREAD_FUNC_TYPE ;
typedef  scalar_t__ SRes ;
typedef  int /*<<< orphan*/  CMtSync ;

/* Variables and functions */
 scalar_t__ MtSync_Create2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MtSync_Destruct (int /*<<< orphan*/ *) ; 
 scalar_t__ SZ_OK ; 

__attribute__((used)) static SRes MtSync_Create(CMtSync *p, THREAD_FUNC_TYPE startAddress, void *obj, UInt32 numBlocks)
{
  SRes res = MtSync_Create2(p, startAddress, obj, numBlocks);
  if (res != SZ_OK)
    MtSync_Destruct(p);
  return res;
}