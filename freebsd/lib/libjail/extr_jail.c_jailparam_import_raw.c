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
struct jailparam {size_t jp_valuelen; int /*<<< orphan*/  jp_flags; void* jp_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  JP_RAWVALUE ; 

int
jailparam_import_raw(struct jailparam *jp, void *value, size_t valuelen)
{

	jp->jp_value = value;
	jp->jp_valuelen = valuelen;
	jp->jp_flags |= JP_RAWVALUE;
	return (0);
}