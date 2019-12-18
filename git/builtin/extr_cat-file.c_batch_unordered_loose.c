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

/* Variables and functions */
 int batch_unordered_object (struct object_id const*,void*) ; 

__attribute__((used)) static int batch_unordered_loose(const struct object_id *oid,
				 const char *path,
				 void *data)
{
	return batch_unordered_object(oid, data);
}