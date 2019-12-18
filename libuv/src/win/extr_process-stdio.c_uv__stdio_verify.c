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
typedef  scalar_t__ WORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 unsigned int CHILD_STDIO_COUNT (int /*<<< orphan*/ *) ; 
 scalar_t__ CHILD_STDIO_SIZE (unsigned int) ; 

int uv__stdio_verify(BYTE* buffer, WORD size) {
  unsigned int count;

  /* Check the buffer pointer. */
  if (buffer == NULL)
    return 0;

  /* Verify that the buffer is at least big enough to hold the count. */
  if (size < CHILD_STDIO_SIZE(0))
    return 0;

  /* Verify if the count is within range. */
  count = CHILD_STDIO_COUNT(buffer);
  if (count > 256)
    return 0;

  /* Verify that the buffer size is big enough to hold info for N FDs. */
  if (size < CHILD_STDIO_SIZE(count))
    return 0;

  return 1;
}