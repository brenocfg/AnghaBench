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
typedef  int u64 ;

/* Variables and functions */

u64 rotr64 (const u64 a, const int n)
{
  #if defined (_MSC_VER)
  return _rotr64 (a, n);
  #else
  return ((a >> n) | (a << (64 - n)));
  #endif
}