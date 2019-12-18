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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  __bss_end__ ; 
 int /*<<< orphan*/  __bss_start__ ; 
 int /*<<< orphan*/  __data_end__ ; 
 int /*<<< orphan*/  __data_start__ ; 
 int /*<<< orphan*/  __etext ; 
 int /*<<< orphan*/  main () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void Reset_Handler(void)
{
  /* Copy data segment contents from flash to RAM. */
  uint32_t data_bytes = (&__data_end__ - &__data_start__) * 4;
  memcpy(&__etext, &__data_start__, data_bytes);

  /* Zero BSS. */
  uint32_t bss_bytes = (&__bss_end__ - &__bss_start__) * 4;
  memset(&__bss_start__, 0, bss_bytes);

  main();
  while (1)
    ;
}