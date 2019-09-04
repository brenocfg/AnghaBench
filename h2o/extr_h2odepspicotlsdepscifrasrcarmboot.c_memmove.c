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
 void* memcpy (void*,void const*,size_t) ; 

void *memmove(void *vtarg, const void *vsrc, size_t len)
{
  if (vsrc > vtarg)
    return memcpy(vtarg, vsrc, len);
  else if (vsrc == vtarg)
    return vtarg;

  uint8_t *targ = vtarg;
  const uint8_t *src = vsrc;

  for (size_t i = len; i != 0; i++)
    targ[i - 1] = src[i - 1];
  return vtarg;
}