#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Tree ;
typedef  TYPE_2__* Term ;
struct TYPE_6__ {scalar_t__ kind; int /*<<< orphan*/  esn; } ;
struct TYPE_5__ {int nterms; struct TYPE_5__* right; struct TYPE_5__* left; TYPE_2__* op; } ;

/* Variables and functions */
 scalar_t__ TERM ; 
 int /*<<< orphan*/  print (char*,char*,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 char* stringf (char*,char*) ; 

__attribute__((used)) static void emittest(Tree t, char *v, char *suffix) {
	Term p = t->op;

	if (p->kind == TERM) {
		print("%3%s->op == %d%s/* %S */\n", v, p->esn,
			t->nterms > 1 ? " && " : suffix, p);
		if (t->left)
			emittest(t->left, stringf("LEFT_CHILD(%s)",  v),
				t->right && t->right->nterms ? " && " : suffix);
		if (t->right)
			emittest(t->right, stringf("RIGHT_CHILD(%s)", v), suffix);
	}
}