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
typedef  void* timestamp_t ;
struct reflog_expire_cfg {void* expire_unreachable; void* expire_total; } ;

/* Variables and functions */
#define  EXPIRE_TOTAL 129 
#define  EXPIRE_UNREACH 128 
 void* default_reflog_expire ; 
 void* default_reflog_expire_unreachable ; 
 struct reflog_expire_cfg* find_cfg_ent (char const*,int) ; 
 scalar_t__ git_config_expiry_date (void**,char const*,char const*) ; 
 int git_default_config (char const*,char const*,void*) ; 
 scalar_t__ parse_config_key (char const*,char*,char const**,int*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int reflog_expire_config(const char *var, const char *value, void *cb)
{
	const char *pattern, *key;
	int pattern_len;
	timestamp_t expire;
	int slot;
	struct reflog_expire_cfg *ent;

	if (parse_config_key(var, "gc", &pattern, &pattern_len, &key) < 0)
		return git_default_config(var, value, cb);

	if (!strcmp(key, "reflogexpire")) {
		slot = EXPIRE_TOTAL;
		if (git_config_expiry_date(&expire, var, value))
			return -1;
	} else if (!strcmp(key, "reflogexpireunreachable")) {
		slot = EXPIRE_UNREACH;
		if (git_config_expiry_date(&expire, var, value))
			return -1;
	} else
		return git_default_config(var, value, cb);

	if (!pattern) {
		switch (slot) {
		case EXPIRE_TOTAL:
			default_reflog_expire = expire;
			break;
		case EXPIRE_UNREACH:
			default_reflog_expire_unreachable = expire;
			break;
		}
		return 0;
	}

	ent = find_cfg_ent(pattern, pattern_len);
	if (!ent)
		return -1;
	switch (slot) {
	case EXPIRE_TOTAL:
		ent->expire_total = expire;
		break;
	case EXPIRE_UNREACH:
		ent->expire_unreachable = expire;
		break;
	}
	return 0;
}