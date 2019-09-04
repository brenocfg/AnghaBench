#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  count; scalar_t__ name; } ;
typedef  TYPE_1__ name_data ;

/* Variables and functions */
 int GIT_ERROR ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static int update_count(name_data *data, const char *name)
{
	name_data *n;

	for (n = data; n->name; n++) {
		if (!strcmp(n->name, name)) {
			n->count++;
			return 0;
		}
	}

	return GIT_ERROR;
}