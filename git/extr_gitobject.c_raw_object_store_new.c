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
struct raw_object_store {int /*<<< orphan*/  packed_git_mru; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct raw_object_store*,int /*<<< orphan*/ ,int) ; 
 struct raw_object_store* xmalloc (int) ; 

struct raw_object_store *raw_object_store_new(void)
{
	struct raw_object_store *o = xmalloc(sizeof(*o));

	memset(o, 0, sizeof(*o));
	INIT_LIST_HEAD(&o->packed_git_mru);
	return o;
}