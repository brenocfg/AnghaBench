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
struct servent {char* s_name; char** s_aliases; int /*<<< orphan*/  s_proto; } ;

/* Variables and functions */
 scalar_t__ compare_servent (struct servent*,struct servent*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_servent (struct servent*) ; 
 struct servent* getservbyname (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ servent_check_ambiguity (struct servent_test_data*,struct servent*) ; 
 scalar_t__ servent_test_correctness (struct servent*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
servent_test_getservbyname(struct servent *serv_model, void *mdata)
{
	char **alias;
	struct servent *serv;

	printf("testing getservbyname() with the following data:\n");
	dump_servent(serv_model);

	serv = getservbyname(serv_model->s_name, serv_model->s_proto);
	if (servent_test_correctness(serv, NULL) != 0)
		goto errfin;

	if ((compare_servent(serv, serv_model, NULL) != 0) &&
	    (servent_check_ambiguity((struct servent_test_data *)mdata, serv)
	    !=0))
		goto errfin;

	for (alias = serv_model->s_aliases; *alias; ++alias) {
		serv = getservbyname(*alias, serv_model->s_proto);

		if (servent_test_correctness(serv, NULL) != 0)
			goto errfin;

		if ((compare_servent(serv, serv_model, NULL) != 0) &&
		    (servent_check_ambiguity(
		    (struct servent_test_data *)mdata, serv) != 0))
		    goto errfin;
	}

	printf("ok\n");
	return (0);

errfin:
	printf("not ok\n");

	return (-1);
}