#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* name; int scope; struct TYPE_8__* up; } ;
struct entry {TYPE_2__ sym; struct entry* link; } ;
typedef  TYPE_1__* Table ;
struct TYPE_7__ {int level; struct entry** buckets; TYPE_2__* all; } ;
typedef  TYPE_2__* Symbol ;

/* Variables and functions */
 int HASHSIZE ; 
 int /*<<< orphan*/  NEW0 (struct entry*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* table (TYPE_1__*,int) ; 

Symbol install(const char *name, Table *tpp, int level, int arena) {
	Table tp = *tpp;
	struct entry *p;
	unsigned h = (unsigned long)name&(HASHSIZE-1);

	assert(level == 0 || level >= tp->level);
	if (level > 0 && tp->level < level)
		tp = *tpp = table(tp, level);
	NEW0(p, arena);
	p->sym.name = (char *)name;
	p->sym.scope = level;
	p->sym.up = tp->all;
	tp->all = &p->sym;
	p->link = tp->buckets[h];
	tp->buckets[h] = p;
	return &p->sym;
}