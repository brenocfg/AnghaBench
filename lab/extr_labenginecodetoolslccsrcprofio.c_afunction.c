#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int x; int y; scalar_t__ count; } ;
struct func {char* name; TYPE_1__ count; struct func* link; scalar_t__ callers; } ;
struct file {struct func* funcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEW (struct func*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERM ; 
 int /*<<< orphan*/  assert (struct file*) ; 
 scalar_t__ compare (TYPE_1__*,TYPE_1__*) ; 
 struct file* findfile (char*) ; 

__attribute__((used)) static struct func *afunction(char *name, char *file, int x, int y, int count) {
	struct file *p = findfile(file);
	struct func *q;

	assert(p);
	for (q = p->funcs; q && name != q->name; q = q->link)
		;
	if (!q) {
		struct func **r;
		NEW(q, PERM);
		q->name = name;
		q->count.x = x;
		q->count.y = y;
		q->count.count = 0;
		q->callers = 0;
		for (r = &p->funcs; *r && compare(&q->count, &(*r)->count) > 0; r = &(*r)->link)
			;
		q->link = *r;
		*r = q;
	}
	q->count.count += count;
	return q;
}