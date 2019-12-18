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
struct suffix_code_t {char* member_0; char* member_1; } ;

/* Variables and functions */
 char const* get_suffix_code (struct suffix_code_t const*,char const*) ; 

__attribute__((used)) static const char *
decompose_alias(const char *suffix)
{
	static const struct suffix_code_t alias[] = {
		{ ".taz",	".tar.gz" },
		{ ".tgz",	".tar.gz" },
		{ ".tbz",	".tar.bz2" },
		{ ".tbz2",	".tar.bz2" },
		{ ".tz2",	".tar.bz2" },
		{ ".tlz",	".tar.lzma" },
		{ ".txz",	".tar.xz" },
		{ ".tzo",	".tar.lzo" },
		{ ".taZ",	".tar.Z" },
		{ ".tZ",	".tar.Z" },
		{ ".tzst",	".tar.zst" },
		{ NULL,		NULL }
	};

	return get_suffix_code(alias, suffix);
}