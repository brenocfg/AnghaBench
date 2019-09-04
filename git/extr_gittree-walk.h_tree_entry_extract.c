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
struct object_id {int dummy; } ;
struct TYPE_2__ {char* path; unsigned int mode; struct object_id const oid; } ;
struct tree_desc {TYPE_1__ entry; } ;

/* Variables and functions */

__attribute__((used)) static inline const struct object_id *tree_entry_extract(struct tree_desc *desc, const char **pathp, unsigned int *modep)
{
	*pathp = desc->entry.path;
	*modep = desc->entry.mode;
	return &desc->entry.oid;
}