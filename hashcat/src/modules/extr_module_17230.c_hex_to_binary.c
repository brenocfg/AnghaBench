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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 char hex_to_u8 (int /*<<< orphan*/  const*) ; 

void hex_to_binary (const char *source, int len, char* out)
{
  for (int i = 0, j = 0; j < len; i += 1, j += 2)
  {
    out[i] = hex_to_u8 ((const u8 *) &source[j]);
  }
}