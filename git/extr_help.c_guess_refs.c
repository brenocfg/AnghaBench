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
struct string_list {int dummy; } ;
struct similar_ref_cb {char const* base_ref; struct string_list* similar_refs; } ;

/* Variables and functions */
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  append_similar_ref ; 
 int /*<<< orphan*/  for_each_ref (int /*<<< orphan*/ ,struct similar_ref_cb*) ; 

__attribute__((used)) static struct string_list guess_refs(const char *ref)
{
	struct similar_ref_cb ref_cb;
	struct string_list similar_refs = STRING_LIST_INIT_DUP;

	ref_cb.base_ref = ref;
	ref_cb.similar_refs = &similar_refs;
	for_each_ref(append_similar_ref, &ref_cb);
	return similar_refs;
}