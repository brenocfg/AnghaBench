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
struct nptv6_dump_arg {int /*<<< orphan*/  ch; int /*<<< orphan*/  sd; } ;
struct nptv6_cfg {int dummy; } ;
struct namedobj_instance {int dummy; } ;
struct named_object {int dummy; } ;
typedef  int /*<<< orphan*/  ipfw_nptv6_cfg ;

/* Variables and functions */
 scalar_t__ ipfw_get_sopt_space (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nptv6_export_config (int /*<<< orphan*/ ,struct nptv6_cfg*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
export_config_cb(struct namedobj_instance *ni, struct named_object *no,
    void *arg)
{
	struct nptv6_dump_arg *da = (struct nptv6_dump_arg *)arg;
	ipfw_nptv6_cfg *uc;

	uc = (ipfw_nptv6_cfg *)ipfw_get_sopt_space(da->sd, sizeof(*uc));
	nptv6_export_config(da->ch, (struct nptv6_cfg *)no, uc);
	return (0);
}