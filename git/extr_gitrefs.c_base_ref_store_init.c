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
struct ref_store {struct ref_storage_be const* be; } ;
struct ref_storage_be {int dummy; } ;

/* Variables and functions */

void base_ref_store_init(struct ref_store *refs,
			 const struct ref_storage_be *be)
{
	refs->be = be;
}