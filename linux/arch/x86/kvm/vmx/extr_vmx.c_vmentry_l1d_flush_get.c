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
struct kernel_param {int dummy; } ;
struct TYPE_3__ {char* option; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 size_t l1tf_vmx_mitigation ; 
 int sprintf (char*,char*,...) ; 
 TYPE_1__* vmentry_l1d_param ; 

__attribute__((used)) static int vmentry_l1d_flush_get(char *s, const struct kernel_param *kp)
{
	if (WARN_ON_ONCE(l1tf_vmx_mitigation >= ARRAY_SIZE(vmentry_l1d_param)))
		return sprintf(s, "???\n");

	return sprintf(s, "%s\n", vmentry_l1d_param[l1tf_vmx_mitigation].option);
}