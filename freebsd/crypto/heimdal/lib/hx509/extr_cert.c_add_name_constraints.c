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
struct TYPE_3__ {int len; int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ hx509_name_constraints ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  NameConstraints ;
typedef  int /*<<< orphan*/  Certificate ;

/* Variables and functions */
 int ENOMEM ; 
 int HX509_EXTENSION_NOT_FOUND ; 
 int HX509_VERIFY_CONSTRAINTS ; 
 int copy_NameConstraints (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int find_extension_name_constraints (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_NameConstraints (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
add_name_constraints(hx509_context context, const Certificate *c, int not_ca,
		     hx509_name_constraints *nc)
{
    NameConstraints tnc;
    int ret;

    ret = find_extension_name_constraints(c, &tnc);
    if (ret == HX509_EXTENSION_NOT_FOUND)
	return 0;
    else if (ret) {
	hx509_set_error_string(context, 0, ret, "Failed getting NameConstraints");
	return ret;
    } else if (not_ca) {
	ret = HX509_VERIFY_CONSTRAINTS;
	hx509_set_error_string(context, 0, ret, "Not a CA and "
			       "have NameConstraints");
    } else {
	NameConstraints *val;
	val = realloc(nc->val, sizeof(nc->val[0]) * (nc->len + 1));
	if (val == NULL) {
	    hx509_clear_error_string(context);
	    ret = ENOMEM;
	    goto out;
	}
	nc->val = val;
	ret = copy_NameConstraints(&tnc, &nc->val[nc->len]);
	if (ret) {
	    hx509_clear_error_string(context);
	    goto out;
	}
	nc->len += 1;
    }
out:
    free_NameConstraints(&tnc);
    return ret;
}