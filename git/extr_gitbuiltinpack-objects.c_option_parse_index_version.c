#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct option {int dummy; } ;
struct TYPE_2__ {int version; int off32_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__ pack_idx_opts ; 
 void* strtoul (char const*,char**,int) ; 

__attribute__((used)) static int option_parse_index_version(const struct option *opt,
				      const char *arg, int unset)
{
	char *c;
	const char *val = arg;

	BUG_ON_OPT_NEG(unset);

	pack_idx_opts.version = strtoul(val, &c, 10);
	if (pack_idx_opts.version > 2)
		die(_("unsupported index version %s"), val);
	if (*c == ',' && c[1])
		pack_idx_opts.off32_limit = strtoul(c+1, &c, 0);
	if (*c || pack_idx_opts.off32_limit & 0x80000000)
		die(_("bad index version '%s'"), val);
	return 0;
}