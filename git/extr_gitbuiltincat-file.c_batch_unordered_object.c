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
struct object_id {int dummy; } ;
struct object_cb_data {int /*<<< orphan*/  seen; } ;

/* Variables and functions */
 int batch_object_cb (struct object_id const*,struct object_cb_data*) ; 
 scalar_t__ oidset_insert (int /*<<< orphan*/ ,struct object_id const*) ; 

__attribute__((used)) static int batch_unordered_object(const struct object_id *oid, void *vdata)
{
	struct object_cb_data *data = vdata;

	if (oidset_insert(data->seen, oid))
		return 0;

	return batch_object_cb(oid, data);
}