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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 size_t MRB_DUMP_ALIGNMENT ; 

__attribute__((used)) static size_t
skip_padding(const uint8_t *buf)
{
  const size_t align = MRB_DUMP_ALIGNMENT;
  return -(intptr_t)buf & (align-1);
}