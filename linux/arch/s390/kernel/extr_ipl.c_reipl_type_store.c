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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPL_CCW_STR ; 
 int /*<<< orphan*/  IPL_FCP_STR ; 
 int /*<<< orphan*/  IPL_NSS_STR ; 
 int /*<<< orphan*/  IPL_TYPE_CCW ; 
 int /*<<< orphan*/  IPL_TYPE_FCP ; 
 int /*<<< orphan*/  IPL_TYPE_NSS ; 
 int reipl_set_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t reipl_type_store(struct kobject *kobj,
				struct kobj_attribute *attr,
				const char *buf, size_t len)
{
	int rc = -EINVAL;

	if (strncmp(buf, IPL_CCW_STR, strlen(IPL_CCW_STR)) == 0)
		rc = reipl_set_type(IPL_TYPE_CCW);
	else if (strncmp(buf, IPL_FCP_STR, strlen(IPL_FCP_STR)) == 0)
		rc = reipl_set_type(IPL_TYPE_FCP);
	else if (strncmp(buf, IPL_NSS_STR, strlen(IPL_NSS_STR)) == 0)
		rc = reipl_set_type(IPL_TYPE_NSS);
	return (rc != 0) ? rc : len;
}