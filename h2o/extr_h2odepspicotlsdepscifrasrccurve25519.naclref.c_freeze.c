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

/* Variables and functions */
 int /*<<< orphan*/  add (unsigned int*,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minusp ; 

__attribute__((used)) static void freeze(unsigned int a[32])
{
  unsigned int aorig[32];
  unsigned int j;
  unsigned int negative;

  for (j = 0;j < 32;++j) aorig[j] = a[j];
  add(a,a,minusp);
  negative = -((a[31] >> 7) & 1);
  for (j = 0;j < 32;++j) a[j] ^= negative & (aorig[j] ^ a[j]);
}