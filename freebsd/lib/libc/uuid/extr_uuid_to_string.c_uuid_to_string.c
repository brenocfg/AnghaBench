#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * node; int /*<<< orphan*/  clock_seq_low; int /*<<< orphan*/  clock_seq_hi_and_reserved; int /*<<< orphan*/  time_hi_and_version; int /*<<< orphan*/  time_mid; int /*<<< orphan*/  time_low; } ;
typedef  TYPE_1__ uuid_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_create_nil (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uuid_s_no_memory ; 
 int /*<<< orphan*/  uuid_s_ok ; 

void
uuid_to_string(const uuid_t *u, char **s, uint32_t *status)
{
	uuid_t nil;

	if (status != NULL)
		*status = uuid_s_ok;

	/* Why allow a NULL-pointer here? */
	if (s == NULL)
		return;

	if (u == NULL) {
		u = &nil;
		uuid_create_nil(&nil, NULL);
	}

	asprintf(s, "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
	    u->time_low, u->time_mid, u->time_hi_and_version,
	    u->clock_seq_hi_and_reserved, u->clock_seq_low, u->node[0],
	    u->node[1], u->node[2], u->node[3], u->node[4], u->node[5]);

	if (*s == NULL && status != NULL)
		*status = uuid_s_no_memory;
}