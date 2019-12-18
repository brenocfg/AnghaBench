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
struct passwd_test_data {int dummy; } ;
struct passwd {int /*<<< orphan*/  pw_name; } ;

/* Variables and functions */
 scalar_t__ compare_passwd (struct passwd*,struct passwd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_passwd (struct passwd*) ; 
 struct passwd* getpwnam (int /*<<< orphan*/ ) ; 
 scalar_t__ passwd_check_ambiguity (struct passwd_test_data*,struct passwd*) ; 
 scalar_t__ passwd_test_correctness (struct passwd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
passwd_test_getpwnam(struct passwd *pwd_model, void *mdata)
{
	struct passwd *pwd;

#ifdef DEBUG
	printf("testing getpwnam() with the following data:\n");
	dump_passwd(pwd_model);
#endif

	pwd = getpwnam(pwd_model->pw_name);
	if (passwd_test_correctness(pwd, NULL) != 0)
		goto errfin;

	if ((compare_passwd(pwd, pwd_model, NULL) != 0) &&
	    (passwd_check_ambiguity((struct passwd_test_data *)mdata, pwd)
	    !=0))
	    goto errfin;

#ifdef DEBUG
	printf("ok\n");
#endif
	return (0);

errfin:
#ifdef DEBUG
	printf("not ok\n");
#endif
	return (-1);
}