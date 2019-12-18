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
typedef  size_t u32 ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t JRSTA_SSRC_SHIFT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,size_t,...) ; 
#define  report_ccb_status 133 
#define  report_cond_code_status 132 
#define  report_deco_status 131 
#define  report_jr_status 130 
#define  report_jump_status 129 
#define  report_qi_status 128 
 int stub1 (struct device*,size_t,char const*) ; 

int caam_strstatus(struct device *jrdev, u32 status, bool qi_v2)
{
	static const struct stat_src {
		int (*report_ssed)(struct device *jrdev, const u32 status,
				   const char *error);
		const char *error;
	} status_src[16] = {
		{ NULL, "No error" },
		{ NULL, NULL },
		{ report_ccb_status, "CCB" },
		{ report_jump_status, "Jump" },
		{ report_deco_status, "DECO" },
		{ report_qi_status, "Queue Manager Interface" },
		{ report_jr_status, "Job Ring" },
		{ report_cond_code_status, "Condition Code" },
		{ NULL, NULL },
		{ NULL, NULL },
		{ NULL, NULL },
		{ NULL, NULL },
		{ NULL, NULL },
		{ NULL, NULL },
		{ NULL, NULL },
		{ NULL, NULL },
	};
	u32 ssrc = status >> JRSTA_SSRC_SHIFT;
	const char *error = status_src[ssrc].error;

	/*
	 * If there is an error handling function, call it to report the error.
	 * Otherwise print the error source name.
	 */
	if (status_src[ssrc].report_ssed)
		return status_src[ssrc].report_ssed(jrdev, status, error);

	if (error)
		dev_err(jrdev, "%d: %s\n", ssrc, error);
	else
		dev_err(jrdev, "%d: unknown error source\n", ssrc);

	return -EINVAL;
}