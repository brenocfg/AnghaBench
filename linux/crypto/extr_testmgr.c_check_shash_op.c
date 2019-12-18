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
struct testvec_config {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,char const*,char const*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int check_shash_op(const char *op, int err,
				 const char *driver, const char *vec_name,
				 const struct testvec_config *cfg)
{
	if (err)
		pr_err("alg: shash: %s %s() failed with err %d on test vector %s, cfg=\"%s\"\n",
		       driver, op, err, vec_name, cfg->name);
	return err;
}