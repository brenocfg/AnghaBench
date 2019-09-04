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
struct ref_store {int dummy; } ;
typedef  int /*<<< orphan*/  each_ref_fn ;

/* Variables and functions */
 int do_for_each_ref (struct ref_store*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int refs_for_each_ref(struct ref_store *refs, each_ref_fn fn, void *cb_data)
{
	return do_for_each_ref(refs, "", fn, 0, 0, cb_data);
}