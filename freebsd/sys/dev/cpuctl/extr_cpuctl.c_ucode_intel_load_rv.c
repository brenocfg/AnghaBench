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
struct ucode_update_data {scalar_t__ cpu; int /*<<< orphan*/  ptr; int /*<<< orphan*/  ret; } ;

/* Variables and functions */
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  ucode_intel_load (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ucode_intel_load_rv(void *arg)
{
	struct ucode_update_data *d;

	d = arg;
	if (PCPU_GET(cpuid) == d->cpu)
		d->ret = ucode_intel_load(d->ptr, true, NULL, NULL);
}