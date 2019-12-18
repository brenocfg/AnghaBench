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
struct protoent_test_data {int dummy; } ;
struct protoent {char* p_name; char** p_aliases; } ;

/* Variables and functions */
 scalar_t__ compare_protoent (struct protoent*,struct protoent*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_protoent (struct protoent*) ; 
 struct protoent* getprotobyname (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ protoent_check_ambiguity (struct protoent_test_data*,struct protoent*) ; 
 scalar_t__ protoent_test_correctness (struct protoent*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
protoent_test_getprotobyname(struct protoent *pe_model, void *mdata)
{
	char **alias;
	struct protoent *pe;

	printf("testing getprotobyname() with the following data:\n");
	dump_protoent(pe_model);

	pe = getprotobyname(pe_model->p_name);
	if (protoent_test_correctness(pe, NULL) != 0)
		goto errfin;

	if ((compare_protoent(pe, pe_model, NULL) != 0) &&
	    (protoent_check_ambiguity((struct protoent_test_data *)mdata, pe)
	    !=0))
	    goto errfin;

	for (alias = pe_model->p_aliases; *alias; ++alias) {
		pe = getprotobyname(*alias);

		if (protoent_test_correctness(pe, NULL) != 0)
			goto errfin;

		if ((compare_protoent(pe, pe_model, NULL) != 0) &&
		    (protoent_check_ambiguity(
		    (struct protoent_test_data *)mdata, pe) != 0))
		    goto errfin;
	}

	printf("ok\n");
	return (0);

errfin:
	printf("not ok\n");

	return (-1);
}