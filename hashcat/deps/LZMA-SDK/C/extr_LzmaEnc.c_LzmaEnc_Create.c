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
typedef  int /*<<< orphan*/  ISzAllocPtr ;
typedef  void* CLzmaEncHandle ;
typedef  int /*<<< orphan*/  CLzmaEnc ;

/* Variables and functions */
 void* ISzAlloc_Alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LzmaEnc_Construct (int /*<<< orphan*/ *) ; 

CLzmaEncHandle LzmaEnc_Create(ISzAllocPtr alloc)
{
  void *p;
  p = ISzAlloc_Alloc(alloc, sizeof(CLzmaEnc));
  if (p)
    LzmaEnc_Construct((CLzmaEnc *)p);
  return p;
}