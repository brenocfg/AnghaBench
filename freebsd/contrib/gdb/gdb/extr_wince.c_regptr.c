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
typedef  int /*<<< orphan*/  ULONG ;
typedef  scalar_t__ LPCONTEXT ;

/* Variables and functions */
 scalar_t__* mappings ; 

__attribute__((used)) static ULONG *
regptr (LPCONTEXT c, int r)
{
  static ULONG zero = 0;
  ULONG *p;
  if (mappings[r] < 0)
    p = &zero;
  else
    p = (ULONG *) (((char *) c) + mappings[r]);
  return p;
}