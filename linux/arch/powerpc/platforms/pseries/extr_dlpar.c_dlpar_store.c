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
struct pseries_hp_errorlog {int dummy; } ;
struct class_attribute {int dummy; } ;
struct class {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dlpar_parse_action (char**,struct pseries_hp_errorlog*) ; 
 int dlpar_parse_id_type (char**,struct pseries_hp_errorlog*) ; 
 int dlpar_parse_resource (char**,struct pseries_hp_errorlog*) ; 
 int handle_dlpar_errorlog (struct pseries_hp_errorlog*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static ssize_t dlpar_store(struct class *class, struct class_attribute *attr,
			   const char *buf, size_t count)
{
	struct pseries_hp_errorlog hp_elog;
	char *argbuf;
	char *args;
	int rc;

	args = argbuf = kstrdup(buf, GFP_KERNEL);
	if (!argbuf) {
		pr_info("Could not allocate resources for DLPAR operation\n");
		kfree(argbuf);
		return -ENOMEM;
	}

	/*
	 * Parse out the request from the user, this will be in the form:
	 * <resource> <action> <id_type> <id>
	 */
	rc = dlpar_parse_resource(&args, &hp_elog);
	if (rc)
		goto dlpar_store_out;

	rc = dlpar_parse_action(&args, &hp_elog);
	if (rc)
		goto dlpar_store_out;

	rc = dlpar_parse_id_type(&args, &hp_elog);
	if (rc)
		goto dlpar_store_out;

	rc = handle_dlpar_errorlog(&hp_elog);

dlpar_store_out:
	kfree(argbuf);

	if (rc)
		pr_err("Could not handle DLPAR request \"%s\"\n", buf);

	return rc ? rc : count;
}