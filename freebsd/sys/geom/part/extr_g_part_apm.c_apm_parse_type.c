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
 int /*<<< orphan*/  APM_ENT_TYPE_APPLE_BOOT ; 
 int /*<<< orphan*/  APM_ENT_TYPE_APPLE_HFS ; 
 int /*<<< orphan*/  APM_ENT_TYPE_APPLE_UFS ; 
 int /*<<< orphan*/  APM_ENT_TYPE_FREEBSD ; 
 int /*<<< orphan*/  APM_ENT_TYPE_FREEBSD_NANDFS ; 
 int /*<<< orphan*/  APM_ENT_TYPE_FREEBSD_SWAP ; 
 int /*<<< orphan*/  APM_ENT_TYPE_FREEBSD_UFS ; 
 int /*<<< orphan*/  APM_ENT_TYPE_FREEBSD_VINUM ; 
 int /*<<< orphan*/  APM_ENT_TYPE_FREEBSD_ZFS ; 
 int /*<<< orphan*/  APM_ENT_TYPE_SELF ; 
 int /*<<< orphan*/  APM_ENT_TYPE_UNUSED ; 
 int EINVAL ; 
 int /*<<< orphan*/  G_PART_ALIAS_APPLE_BOOT ; 
 int /*<<< orphan*/  G_PART_ALIAS_APPLE_HFS ; 
 int /*<<< orphan*/  G_PART_ALIAS_APPLE_UFS ; 
 int /*<<< orphan*/  G_PART_ALIAS_FREEBSD ; 
 int /*<<< orphan*/  G_PART_ALIAS_FREEBSD_NANDFS ; 
 int /*<<< orphan*/  G_PART_ALIAS_FREEBSD_SWAP ; 
 int /*<<< orphan*/  G_PART_ALIAS_FREEBSD_UFS ; 
 int /*<<< orphan*/  G_PART_ALIAS_FREEBSD_VINUM ; 
 int /*<<< orphan*/  G_PART_ALIAS_FREEBSD_ZFS ; 
 char* g_part_alias_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static int
apm_parse_type(const char *type, char *buf, size_t bufsz)
{
	const char *alias;

	if (type[0] == '!') {
		type++;
		if (strlen(type) > bufsz)
			return (EINVAL);
		if (!strcmp(type, APM_ENT_TYPE_SELF) ||
		    !strcmp(type, APM_ENT_TYPE_UNUSED))
			return (EINVAL);
		strncpy(buf, type, bufsz);
		return (0);
	}
	alias = g_part_alias_name(G_PART_ALIAS_APPLE_BOOT);
	if (!strcasecmp(type, alias)) {
		strcpy(buf, APM_ENT_TYPE_APPLE_BOOT);
		return (0);
	}
	alias = g_part_alias_name(G_PART_ALIAS_APPLE_HFS);
	if (!strcasecmp(type, alias)) {
		strcpy(buf, APM_ENT_TYPE_APPLE_HFS);
		return (0);
	}
	alias = g_part_alias_name(G_PART_ALIAS_APPLE_UFS);
	if (!strcasecmp(type, alias)) {
		strcpy(buf, APM_ENT_TYPE_APPLE_UFS);
		return (0);
	}
	alias = g_part_alias_name(G_PART_ALIAS_FREEBSD);
	if (!strcasecmp(type, alias)) {
		strcpy(buf, APM_ENT_TYPE_FREEBSD);
		return (0);
	}
	alias = g_part_alias_name(G_PART_ALIAS_FREEBSD_NANDFS);
	if (!strcasecmp(type, alias)) {
		strcpy(buf, APM_ENT_TYPE_FREEBSD_NANDFS);
		return (0);
	}
	alias = g_part_alias_name(G_PART_ALIAS_FREEBSD_SWAP);
	if (!strcasecmp(type, alias)) {
		strcpy(buf, APM_ENT_TYPE_FREEBSD_SWAP);
		return (0);
	}
	alias = g_part_alias_name(G_PART_ALIAS_FREEBSD_UFS);
	if (!strcasecmp(type, alias)) {
		strcpy(buf, APM_ENT_TYPE_FREEBSD_UFS);
		return (0);
	}
	alias = g_part_alias_name(G_PART_ALIAS_FREEBSD_VINUM);
	if (!strcasecmp(type, alias)) {
		strcpy(buf, APM_ENT_TYPE_FREEBSD_VINUM);
		return (0);
	}
	alias = g_part_alias_name(G_PART_ALIAS_FREEBSD_ZFS);
	if (!strcasecmp(type, alias)) {
		strcpy(buf, APM_ENT_TYPE_FREEBSD_ZFS);
		return (0);
	}
	return (EINVAL);
}