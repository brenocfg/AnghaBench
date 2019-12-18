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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  G_PART_ALIAS_FREEBSD_NANDFS ; 
 int /*<<< orphan*/  G_PART_ALIAS_FREEBSD_SWAP ; 
 int /*<<< orphan*/  G_PART_ALIAS_FREEBSD_UFS ; 
 int /*<<< orphan*/  G_PART_ALIAS_FREEBSD_VINUM ; 
 int /*<<< orphan*/  G_PART_ALIAS_FREEBSD_ZFS ; 
 scalar_t__ VTOC_TAG_FREEBSD_NANDFS ; 
 scalar_t__ VTOC_TAG_FREEBSD_SWAP ; 
 scalar_t__ VTOC_TAG_FREEBSD_UFS ; 
 scalar_t__ VTOC_TAG_FREEBSD_VINUM ; 
 scalar_t__ VTOC_TAG_FREEBSD_ZFS ; 
 char* g_part_alias_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char const*) ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vtoc8_parse_type(const char *type, uint16_t *tag)
{
	const char *alias;
	char *endp;
	long lt;

	if (type[0] == '!') {
		lt = strtol(type + 1, &endp, 0);
		if (type[1] == '\0' || *endp != '\0' || lt <= 0 ||
		    lt >= 65536)
			return (EINVAL);
		*tag = (uint16_t)lt;
		return (0);
	}
	alias = g_part_alias_name(G_PART_ALIAS_FREEBSD_NANDFS);
	if (!strcasecmp(type, alias)) {
		*tag = VTOC_TAG_FREEBSD_NANDFS;
		return (0);
	}
	alias = g_part_alias_name(G_PART_ALIAS_FREEBSD_SWAP);
	if (!strcasecmp(type, alias)) {
		*tag = VTOC_TAG_FREEBSD_SWAP;
		return (0);
	}
	alias = g_part_alias_name(G_PART_ALIAS_FREEBSD_UFS);
	if (!strcasecmp(type, alias)) {
		*tag = VTOC_TAG_FREEBSD_UFS;
		return (0);
	}
	alias = g_part_alias_name(G_PART_ALIAS_FREEBSD_VINUM);
	if (!strcasecmp(type, alias)) {
		*tag = VTOC_TAG_FREEBSD_VINUM;
		return (0);
	}
	alias = g_part_alias_name(G_PART_ALIAS_FREEBSD_ZFS);
	if (!strcasecmp(type, alias)) {
		*tag = VTOC_TAG_FREEBSD_ZFS;
		return (0);
	}
	return (EINVAL);
}