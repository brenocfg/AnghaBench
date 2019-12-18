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

/* Variables and functions */
 int ADE_PARSE ; 
 int /*<<< orphan*/  auditd_log_debug (char*,...) ; 
 int /*<<< orphan*/  auditd_log_err (char*,...) ; 
 int /*<<< orphan*/  auditd_log_notice (char*) ; 
 int auditd_set_evcmap () ; 
 int auditd_set_fsize () ; 
 int auditd_set_host () ; 
 int auditd_set_minfree () ; 
 int auditd_set_namask () ; 
 int auditd_set_policy () ; 
 int auditd_set_qsize () ; 
 int /*<<< orphan*/  auditd_strerror (int) ; 

int
auditd_config_controls(void)
{
	int cnt, err;
	int ret = 0;

	/*
	 * Configure event to class mappings in kernel.
	 */
	cnt = auditd_set_evcmap();
	if (cnt < 0) {
		auditd_log_err("auditd_set_evcmap() failed: %m");
		ret = -1;
	} else if (cnt == 0) {
		auditd_log_err("No events to class mappings registered.");
		ret = -1;
	} else
		auditd_log_debug("Registered %d event to class mappings.", cnt);

	/*
	 * Configure non-attributable event mask in kernel.
	 */
	err = auditd_set_namask();
	if (err) {
		auditd_log_err("auditd_set_namask() %s: %m",
		    auditd_strerror(err));
		ret = -1;
	} else
		auditd_log_debug("Registered non-attributable event mask.");

	/*
	 * Configure audit policy in kernel.
	 */
	err = auditd_set_policy();
	if (err) {
		auditd_log_err("auditd_set_policy() %s: %m",
		    auditd_strerror(err));
		ret = -1;
	} else
		auditd_log_debug("Set audit policy in kernel.");

	/*
	 * Configure audit trail log size in kernel.
	 */
	err = auditd_set_fsize();
	if (err) {
		auditd_log_err("audit_set_fsize() %s: %m",
		    auditd_strerror(err));
		ret = -1;
	} else
		auditd_log_debug("Set audit trail size in kernel.");

	/*
	 * Configure audit trail queue size in kernel.
	 */
	err = auditd_set_qsize();
	if (err) {
		auditd_log_err("audit_set_qsize() %s: %m",
		    auditd_strerror(err));
		ret = -1;
	} else
		auditd_log_debug("Set audit trail queue in kernel.");

	/*
	 * Configure audit trail volume minimum free percentage of blocks in
	 * kernel.
	 */
	err = auditd_set_minfree();
	if (err) {
		auditd_log_err("auditd_set_minfree() %s: %m",
		    auditd_strerror(err));
		ret = -1;
	} else
		auditd_log_debug(
		    "Set audit trail min free percent in kernel.");

	/*
	 * Configure host address in the audit kernel information.
	 */
	err = auditd_set_host();
	if (err) {
		if (err == ADE_PARSE) {
			auditd_log_notice(
			    "audit_control(5) may be missing 'host:' field");
		} else {
			auditd_log_err("auditd_set_host() %s: %m",
			    auditd_strerror(err));
			ret = -1;
		}
	} else
		auditd_log_debug(
		    "Set audit host address information in kernel.");

	return (ret);
}