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
typedef  scalar_t__* gf ;

/* Variables and functions */

__attribute__((used)) static void sub(gf o, const gf a, const gf b)
{
  size_t i;
  for (i = 0; i < 16; i++)
    o[i] = a[i] - b[i];
}