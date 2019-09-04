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
typedef  size_t uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void write_be(uint8_t *out, size_t value, size_t bytes)
{
  while (bytes)
  {
    out[bytes - 1] = value & 0xff;
    value >>= 8;
    bytes--;
  }

  assert(value == 0); /* or we couldn't encode the value. */
}