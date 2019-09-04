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
struct remote {int dummy; } ;
struct ref {struct ref* next; } ;
struct push_cas_option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  apply_cas (struct push_cas_option*,struct remote*,struct ref*) ; 

void apply_push_cas(struct push_cas_option *cas,
		    struct remote *remote,
		    struct ref *remote_refs)
{
	struct ref *ref;
	for (ref = remote_refs; ref; ref = ref->next)
		apply_cas(cas, remote, ref);
}