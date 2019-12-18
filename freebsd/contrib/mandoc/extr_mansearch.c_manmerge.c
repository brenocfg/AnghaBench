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
struct ohash {int dummy; } ;
struct expr {int type; int /*<<< orphan*/  child; } ;

/* Variables and functions */
#define  EXPR_AND 130 
#define  EXPR_OR 129 
#define  EXPR_TERM 128 
 int /*<<< orphan*/  abort () ; 
 struct ohash* manmerge_and (int /*<<< orphan*/ ,struct ohash*) ; 
 struct ohash* manmerge_or (int /*<<< orphan*/ ,struct ohash*) ; 
 struct ohash* manmerge_term (struct expr*,struct ohash*) ; 

__attribute__((used)) static struct ohash *
manmerge(struct expr *e, struct ohash *htab)
{
	switch (e->type) {
	case EXPR_TERM:
		return manmerge_term(e, htab);
	case EXPR_OR:
		return manmerge_or(e->child, htab);
	case EXPR_AND:
		return manmerge_and(e->child, htab);
	default:
		abort();
	}
}