#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ecx; int edx; } ;
typedef  TYPE_1__ vk_cpuid_t ;

/* Variables and functions */
 TYPE_1__* vk_cpuid () ; 

__attribute__((used)) static int aesni256_is_supported (void) {
  vk_cpuid_t *p = vk_cpuid ();
  return (p->ecx & (1 << 25)) && ((p->edx & 0x06000000) == 0x06000000);
}