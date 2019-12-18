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
struct module {int dummy; } ;

/* Variables and functions */
 scalar_t__ fips_enabled ; 
 int /*<<< orphan*/  module_name (struct module*) ; 
 int /*<<< orphan*/  module_sig_ok (struct module*) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void crypto_check_module_sig(struct module *mod)
{
	if (fips_enabled && mod && !module_sig_ok(mod))
		panic("Module %s signature verification failed in FIPS mode\n",
		      module_name(mod));
}