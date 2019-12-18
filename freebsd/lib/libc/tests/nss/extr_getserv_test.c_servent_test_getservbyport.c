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
struct servent_test_data {int dummy; } ;
struct servent {int /*<<< orphan*/  s_proto; int /*<<< orphan*/  s_port; } ;

/* Variables and functions */
 scalar_t__ compare_servent (struct servent*,struct servent*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_servent (struct servent*) ; 
 struct servent* getservbyport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ servent_check_ambiguity (struct servent_test_data*,struct servent*) ; 
 scalar_t__ servent_test_correctness (struct servent*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
servent_test_getservbyport(struct servent *serv_model, void *mdata)
{
	struct servent *serv;

	printf("testing getservbyport() with the following data...\n");
	dump_servent(serv_model);

	serv = getservbyport(serv_model->s_port, serv_model->s_proto);
	if ((servent_test_correctness(serv, NULL) != 0) ||
	    ((compare_servent(serv, serv_model, NULL) != 0) &&
	    (servent_check_ambiguity((struct servent_test_data *)mdata, serv)
	    != 0))) {
		printf("not ok\n");
		return (-1);
	} else {
		printf("ok\n");
		return (0);
	}
}