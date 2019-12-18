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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  err_err_code ;
struct TYPE_3__ {scalar_t__ value; char* error_text; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int const JRSTA_DECOERR_ERROR_MASK ; 
 int const JRSTA_DECOERR_INDEX_MASK ; 
 int const JRSTA_DECOERR_INDEX_SHIFT ; 
 int const JRSTA_DECOERR_JUMP ; 
 TYPE_1__* desc_error_list ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int const,char const*,char*,scalar_t__,char const*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 

__attribute__((used)) static int report_deco_status(struct device *jrdev, const u32 status,
			      const char *error)
{
	u8 err_id = status & JRSTA_DECOERR_ERROR_MASK;
	u8 idx = (status & JRSTA_DECOERR_INDEX_MASK) >>
		  JRSTA_DECOERR_INDEX_SHIFT;
	char *idx_str;
	const char *err_str = "unidentified error value 0x";
	char err_err_code[3] = { 0 };
	int i;

	if (status & JRSTA_DECOERR_JUMP)
		idx_str = "jump tgt desc idx";
	else
		idx_str = "desc idx";

	for (i = 0; i < ARRAY_SIZE(desc_error_list); i++)
		if (desc_error_list[i].value == err_id)
			break;

	if (i != ARRAY_SIZE(desc_error_list) && desc_error_list[i].error_text)
		err_str = desc_error_list[i].error_text;
	else
		snprintf(err_err_code, sizeof(err_err_code), "%02x", err_id);

	dev_err(jrdev, "%08x: %s: %s %d: %s%s\n",
		status, error, idx_str, idx, err_str, err_err_code);

	return -EINVAL;
}