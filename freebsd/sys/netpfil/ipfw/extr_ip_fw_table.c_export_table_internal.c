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
struct table_config {int dummy; } ;
struct namedobj_instance {int dummy; } ;
struct named_object {int dummy; } ;
struct dump_table_args {int /*<<< orphan*/  ch; int /*<<< orphan*/  sd; } ;
typedef  int /*<<< orphan*/  ipfw_xtable_info ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  export_table_info (int /*<<< orphan*/ ,struct table_config*,int /*<<< orphan*/ *) ; 
 scalar_t__ ipfw_get_sopt_space (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
export_table_internal(struct namedobj_instance *ni, struct named_object *no,
    void *arg)
{
	ipfw_xtable_info *i;
	struct dump_table_args *dta;

	dta = (struct dump_table_args *)arg;

	i = (ipfw_xtable_info *)ipfw_get_sopt_space(dta->sd, sizeof(*i));
	KASSERT(i != NULL, ("previously checked buffer is not enough"));

	export_table_info(dta->ch, (struct table_config *)no, i);
	return (0);
}