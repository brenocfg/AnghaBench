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
struct string_list {int dummy; } ;
struct ref {int /*<<< orphan*/  name; struct ref* next; } ;
struct TYPE_2__ {struct ref* util; } ;

/* Variables and functions */
 TYPE_1__* string_list_append_nodup (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_sort (struct string_list*) ; 

__attribute__((used)) static void prepare_ref_index(struct string_list *ref_index, struct ref *ref)
{
	for ( ; ref; ref = ref->next)
		string_list_append_nodup(ref_index, ref->name)->util = ref;

	string_list_sort(ref_index);
}