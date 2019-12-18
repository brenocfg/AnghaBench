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
typedef  int /*<<< orphan*/  uint64_t ;
struct module {int dummy; } ;

/* Variables and functions */
 scalar_t__ in_core (struct module const*,int /*<<< orphan*/ ) ; 
 scalar_t__ in_init (struct module const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
is_internal (const struct module *mod, uint64_t value)
{
	return in_init(mod, value) || in_core(mod, value);
}