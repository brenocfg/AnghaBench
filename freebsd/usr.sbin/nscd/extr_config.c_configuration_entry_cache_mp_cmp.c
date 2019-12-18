#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* cache_entry ;
struct TYPE_4__ {TYPE_1__* params; } ;
struct TYPE_3__ {int /*<<< orphan*/  entry_name; } ;

/* Variables and functions */
 int strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
configuration_entry_cache_mp_cmp(const void *e1, const void *e2)
{
	return (strcmp((const char *)e1,
		(*((cache_entry *)e2))->params->entry_name
		));
}