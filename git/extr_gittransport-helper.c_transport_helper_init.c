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
struct transport {int /*<<< orphan*/ * smart_options; int /*<<< orphan*/ * vtable; struct helper_data* data; } ;
struct helper_data {char const* name; int /*<<< orphan*/  transport_options; } ;

/* Variables and functions */
 int debug ; 
 scalar_t__ getenv (char*) ; 
 int /*<<< orphan*/  transport_check_allowed (char const*) ; 
 int /*<<< orphan*/  vtable ; 
 struct helper_data* xcalloc (int,int) ; 

int transport_helper_init(struct transport *transport, const char *name)
{
	struct helper_data *data = xcalloc(1, sizeof(*data));
	data->name = name;

	transport_check_allowed(name);

	if (getenv("GIT_TRANSPORT_HELPER_DEBUG"))
		debug = 1;

	transport->data = data;
	transport->vtable = &vtable;
	transport->smart_options = &(data->transport_options);
	return 0;
}