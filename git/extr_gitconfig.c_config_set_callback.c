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
struct config_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  configset_add_value (struct config_set*,char const*,char const*) ; 

__attribute__((used)) static int config_set_callback(const char *key, const char *value, void *cb)
{
	struct config_set *cs = cb;
	configset_add_value(cs, key, value);
	return 0;
}