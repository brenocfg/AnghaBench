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
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static size_t
write_padding(uint8_t *buf)
{
  const size_t align = MRB_DUMP_ALIGNMENT;
  size_t pad_len = -(intptr_t)buf & (align-1);
  if (pad_len > 0) {
    memset(buf, 0, pad_len);
  }
  return pad_len;
}