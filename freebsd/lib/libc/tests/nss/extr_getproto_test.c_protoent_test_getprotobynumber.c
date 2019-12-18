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
struct protoent {int /*<<< orphan*/  p_proto; } ;

/* Variables and functions */
 scalar_t__ compare_protoent (struct protoent*,struct protoent*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_protoent (struct protoent*) ; 
 struct protoent* getprotobynumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ protoent_check_ambiguity (struct protoent_test_data*,struct protoent*) ; 
 scalar_t__ protoent_test_correctness (struct protoent*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
protoent_test_getprotobynumber(struct protoent *pe_model, void *mdata)
{
	struct protoent *pe;

	printf("testing getprotobyport() with the following data...\n");
	dump_protoent(pe_model);

	pe = getprotobynumber(pe_model->p_proto);
	if ((protoent_test_correctness(pe, NULL) != 0) ||
	    ((compare_protoent(pe, pe_model, NULL) != 0) &&
	    (protoent_check_ambiguity((struct protoent_test_data *)mdata, pe)
	    != 0))) {
		printf("not ok\n");
		return (-1);
	} else {
		printf("ok\n");
		return (0);
	}
}