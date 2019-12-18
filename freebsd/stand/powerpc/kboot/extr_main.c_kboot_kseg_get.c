#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_2__ {scalar_t__ memsz; scalar_t__ mem; scalar_t__ bufsz; scalar_t__ buf; } ;

/* Variables and functions */
 TYPE_1__* loaded_segments ; 
 int nkexec_segments ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kboot_kseg_get(int *nseg, void **ptr)
{
#if 0
	int a;

	for (a = 0; a < nkexec_segments; a++) {
		printf("kseg_get: %jx %jx %jx %jx\n",
			(uintmax_t)loaded_segments[a].buf,
			(uintmax_t)loaded_segments[a].bufsz,
			(uintmax_t)loaded_segments[a].mem,
			(uintmax_t)loaded_segments[a].memsz);
	}
#endif

	*nseg = nkexec_segments;
	*ptr = &loaded_segments[0];
}