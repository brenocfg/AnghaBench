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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  alt_stfle_fac_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_USING_EXPOLINE ; 
 TYPE_1__ S390_lowcore ; 
 scalar_t__ __is_defined (int /*<<< orphan*/ ) ; 
 scalar_t__ __test_facility (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nospec_disable ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 scalar_t__ test_facility (int) ; 

ssize_t cpu_show_spectre_v2(struct device *dev,
			    struct device_attribute *attr, char *buf)
{
	if (test_facility(156))
		return sprintf(buf, "Mitigation: etokens\n");
	if (__is_defined(CC_USING_EXPOLINE) && !nospec_disable)
		return sprintf(buf, "Mitigation: execute trampolines\n");
	if (__test_facility(82, S390_lowcore.alt_stfle_fac_list))
		return sprintf(buf, "Mitigation: limited branch prediction\n");
	return sprintf(buf, "Vulnerable\n");
}