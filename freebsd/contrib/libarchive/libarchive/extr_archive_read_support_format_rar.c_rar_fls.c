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

__attribute__((used)) static inline int
rar_fls(unsigned int word)
{
  word |= (word >>  1);
  word |= (word >>  2);
  word |= (word >>  4);
  word |= (word >>  8);
  word |= (word >> 16);
  return word - (word >> 1);
}