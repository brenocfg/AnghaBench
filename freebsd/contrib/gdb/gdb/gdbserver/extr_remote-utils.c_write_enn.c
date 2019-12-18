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

void
write_enn (char *buf)
{
  /* Some day, we should define the meanings of the error codes... */
  buf[0] = 'E';
  buf[1] = '0';
  buf[2] = '1';
  buf[3] = '\0';
}