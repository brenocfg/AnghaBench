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
struct kimage {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nodat_stack; } ;

/* Variables and functions */
 int CALL_ON_STACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct kimage*) ; 
 TYPE_1__ S390_lowcore ; 
 int /*<<< orphan*/  do_start_kdump ; 

__attribute__((used)) static bool kdump_csum_valid(struct kimage *image)
{
#ifdef CONFIG_CRASH_DUMP
	int rc;

	rc = CALL_ON_STACK(do_start_kdump, S390_lowcore.nodat_stack, 1, image);
	return rc == 0;
#else
	return false;
#endif
}