#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kstring_t ;
struct TYPE_4__ {int n; size_t* child; char* name; scalar_t__ d; } ;
typedef  TYPE_1__ knhx1_t ;

/* Variables and functions */
 int /*<<< orphan*/  kputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kputsn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void format_node_recur(const knhx1_t *node, const knhx1_t *p, kstring_t *s, char *numbuf)
{
	if (p->n) {
		int i;
		kputc('(', s);
		for (i = 0; i < p->n; ++i) {
			if (i) kputc(',', s);
			format_node_recur(node, &node[p->child[i]], s, numbuf);
		}
		kputc(')', s);
		if (p->name) kputsn(p->name, strlen(p->name), s);
		if (p->d >= 0) {
			sprintf(numbuf, ":%g", p->d);
			kputsn(numbuf, strlen(numbuf), s);
		}
	} else kputsn(p->name, strlen(p->name), s);
}