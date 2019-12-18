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

/* Variables and functions */
 int /*<<< orphan*/  MyFree (void*) ; 
 int /*<<< orphan*/  UNUSED_VAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 

__attribute__((used)) static void SzAlignedFree(ISzAllocPtr pp, void *address)
{
  UNUSED_VAR(pp);
  #ifndef USE_posix_memalign
  if (address)
    MyFree(((void **)address)[-1]);
  #else
  free(address);
  #endif
}