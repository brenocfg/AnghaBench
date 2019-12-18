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
typedef  scalar_t__ u8 ;
struct fst_iface_cfg {char* group_id; int llt; scalar_t__ priority; } ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FST_ATTACH_CMD_PNAME_LLT ; 
 int /*<<< orphan*/  FST_ATTACH_CMD_PNAME_PRIORITY ; 
 int FST_DEFAULT_LLT_CFG_VALUE ; 
 int fst_read_next_int_param (char*,scalar_t__*,char**) ; 
 scalar_t__ fst_read_next_text_param (char const*,char*,int,char**) ; 
 int /*<<< orphan*/  os_strlen (int /*<<< orphan*/ ) ; 
 char* os_strstr (char*,int /*<<< orphan*/ ) ; 

int fst_parse_attach_command(const char *cmd, char *ifname, size_t ifname_size,
			     struct fst_iface_cfg *cfg)
{
	char *pos;
	char *endp;
	Boolean is_valid;
	int val;

	if (fst_read_next_text_param(cmd, ifname, ifname_size, &endp) ||
	    fst_read_next_text_param(endp, cfg->group_id, sizeof(cfg->group_id),
				     &endp))
		return -EINVAL;

	cfg->llt = FST_DEFAULT_LLT_CFG_VALUE;
	cfg->priority = 0;
	pos = os_strstr(endp, FST_ATTACH_CMD_PNAME_LLT);
	if (pos) {
		pos += os_strlen(FST_ATTACH_CMD_PNAME_LLT);
		if (*pos == '=') {
			val = fst_read_next_int_param(pos + 1, &is_valid,
						      &endp);
			if (is_valid)
				cfg->llt = val;
		}
	}
	pos = os_strstr(endp, FST_ATTACH_CMD_PNAME_PRIORITY);
	if (pos) {
		pos += os_strlen(FST_ATTACH_CMD_PNAME_PRIORITY);
		if (*pos == '=') {
			val = fst_read_next_int_param(pos + 1, &is_valid,
						      &endp);
			if (is_valid)
				cfg->priority = (u8) val;
		}
	}

	return 0;
}