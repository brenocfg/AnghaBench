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
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,...) ; 
 char* ocs_strchr (char*,char) ; 
 int /*<<< orphan*/  ocs_strncpy (char*,char*,int) ; 
 char* ocs_strstr (char const*,char const*) ; 

__attribute__((used)) static int32_t
ocs_hw_clp_resp_get_value(ocs_hw_t *hw, const char *keyword, char *value, uint32_t value_len, const char *resp, uint32_t resp_len)
{
	char *start = NULL;
	char *end = NULL;

	/* look for specified keyword in string */
	start = ocs_strstr(resp, keyword);
	if (start == NULL) {
		ocs_log_test(hw->os, "could not find keyword=%s in CLP response\n",
			     keyword);
		return -1;
	}

	/* now look for '=' and go one past */
	start = ocs_strchr(start, '=');
	if (start == NULL) {
		ocs_log_test(hw->os, "could not find \'=\' in CLP response for keyword=%s\n",
			     keyword);
		return -1;
	}
	start++;

	/* \r\n terminates value */
	end = ocs_strstr(start, "\r\n");
	if (end == NULL) {
		ocs_log_test(hw->os, "could not find \\r\\n for keyword=%s in CLP response\n",
			     keyword);
		return -1;
	}

	/* make sure given result array is big enough */
	if ((end - start + 1) > value_len) {
		ocs_log_test(hw->os, "value len=%d not large enough for actual=%ld\n",
			     value_len, (end-start));
		return -1;
	}

	ocs_strncpy(value, start, (end - start));
	value[end-start] = '\0';
	return (end-start+1);
}