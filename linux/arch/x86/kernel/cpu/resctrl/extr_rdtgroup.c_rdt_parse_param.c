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
struct rdt_fs_context {int enable_cdpl3; int enable_cdpl2; int enable_mba_mbps; } ;
struct fs_parse_result {int dummy; } ;
struct fs_parameter {int dummy; } ;
struct fs_context {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  x86_vendor; } ;

/* Variables and functions */
 int EINVAL ; 
#define  Opt_cdp 130 
#define  Opt_cdpl2 129 
#define  Opt_mba_mbps 128 
 int /*<<< orphan*/  X86_VENDOR_INTEL ; 
 TYPE_1__ boot_cpu_data ; 
 int fs_parse (struct fs_context*,int /*<<< orphan*/ *,struct fs_parameter*,struct fs_parse_result*) ; 
 struct rdt_fs_context* rdt_fc2context (struct fs_context*) ; 
 int /*<<< orphan*/  rdt_fs_parameters ; 

__attribute__((used)) static int rdt_parse_param(struct fs_context *fc, struct fs_parameter *param)
{
	struct rdt_fs_context *ctx = rdt_fc2context(fc);
	struct fs_parse_result result;
	int opt;

	opt = fs_parse(fc, &rdt_fs_parameters, param, &result);
	if (opt < 0)
		return opt;

	switch (opt) {
	case Opt_cdp:
		ctx->enable_cdpl3 = true;
		return 0;
	case Opt_cdpl2:
		ctx->enable_cdpl2 = true;
		return 0;
	case Opt_mba_mbps:
		if (boot_cpu_data.x86_vendor != X86_VENDOR_INTEL)
			return -EINVAL;
		ctx->enable_mba_mbps = true;
		return 0;
	}

	return -EINVAL;
}