#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t len; TYPE_1__* val; } ;
typedef  TYPE_2__ hx509_name_constraints ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_4__ {int /*<<< orphan*/  excludedSubtrees; int /*<<< orphan*/  permittedSubtrees; } ;
typedef  int /*<<< orphan*/  GeneralSubtrees ;
typedef  int /*<<< orphan*/  Certificate ;

/* Variables and functions */
 int /*<<< orphan*/  GeneralSubtrees_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int HX509_VERIFY_CONSTRAINTS ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int match_tree (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int*) ; 
 int /*<<< orphan*/  subject_null_p (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
check_name_constraints(hx509_context context,
		       const hx509_name_constraints *nc,
		       const Certificate *c)
{
    int match, ret;
    size_t i;

    for (i = 0 ; i < nc->len; i++) {
	GeneralSubtrees gs;

	if (nc->val[i].permittedSubtrees) {
	    GeneralSubtrees_SET(&gs, nc->val[i].permittedSubtrees);
	    ret = match_tree(&gs, c, &match);
	    if (ret) {
		hx509_clear_error_string(context);
		return ret;
	    }
	    /* allow null subjectNames, they wont matches anything */
	    if (match == 0 && !subject_null_p(c)) {
		hx509_set_error_string(context, 0, HX509_VERIFY_CONSTRAINTS,
				       "Error verify constraints, "
				       "certificate didn't match any "
				       "permitted subtree");
		return HX509_VERIFY_CONSTRAINTS;
	    }
	}
	if (nc->val[i].excludedSubtrees) {
	    GeneralSubtrees_SET(&gs, nc->val[i].excludedSubtrees);
	    ret = match_tree(&gs, c, &match);
	    if (ret) {
		hx509_clear_error_string(context);
		return ret;
	    }
	    if (match) {
		hx509_set_error_string(context, 0, HX509_VERIFY_CONSTRAINTS,
				       "Error verify constraints, "
				       "certificate included in excluded "
				       "subtree");
		return HX509_VERIFY_CONSTRAINTS;
	    }
	}
    }
    return 0;
}