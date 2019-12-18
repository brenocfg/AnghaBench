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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tssp ; 

__attribute__((used)) static __inline uint64_t
vmm_get_host_trbase(void)
{

	return ((uint64_t)PCPU_GET(tssp));
}