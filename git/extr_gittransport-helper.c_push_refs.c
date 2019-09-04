#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct transport {TYPE_1__* vtable; struct helper_data* data; } ;
struct ref {int dummy; } ;
struct helper_data {scalar_t__ export; scalar_t__ push; } ;
struct TYPE_2__ {int (* push_refs ) (struct transport*,struct ref*,int) ;} ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  do_take_over (struct transport*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ process_connect (struct transport*,int) ; 
 int push_refs_with_export (struct transport*,struct ref*,int) ; 
 int push_refs_with_push (struct transport*,struct ref*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (struct transport*,struct ref*,int) ; 

__attribute__((used)) static int push_refs(struct transport *transport,
		struct ref *remote_refs, int flags)
{
	struct helper_data *data = transport->data;

	if (process_connect(transport, 1)) {
		do_take_over(transport);
		return transport->vtable->push_refs(transport, remote_refs, flags);
	}

	if (!remote_refs) {
		fprintf(stderr,
			_("No refs in common and none specified; doing nothing.\n"
			  "Perhaps you should specify a branch such as 'master'.\n"));
		return 0;
	}

	if (data->push)
		return push_refs_with_push(transport, remote_refs, flags);

	if (data->export)
		return push_refs_with_export(transport, remote_refs, flags);

	return -1;
}