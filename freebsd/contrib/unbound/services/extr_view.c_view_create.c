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
struct TYPE_2__ {struct view* key; } ;
struct view {int /*<<< orphan*/  name; int /*<<< orphan*/  lock; TYPE_1__ node; } ;
typedef  int /*<<< orphan*/  rbnode_type ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct view*) ; 
 int /*<<< orphan*/  lock_protect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lock_rw_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static struct view*
view_create(char* name)
{
	struct view* v = (struct view*)calloc(1, sizeof(*v));
	if(!v)
		return NULL;
	v->node.key = v;
	if(!(v->name = strdup(name))) {
		free(v);
		return NULL;
	}
	lock_rw_init(&v->lock);
	lock_protect(&v->lock, &v->name, sizeof(*v)-sizeof(rbnode_type));
	return v;
}