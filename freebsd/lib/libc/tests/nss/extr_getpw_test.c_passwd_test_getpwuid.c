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
struct passwd {int /*<<< orphan*/  pw_uid; } ;

/* Variables and functions */
 scalar_t__ compare_passwd (struct passwd*,struct passwd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_passwd (struct passwd*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 scalar_t__ passwd_check_ambiguity (struct passwd_test_data*,struct passwd*) ; 
 scalar_t__ passwd_test_correctness (struct passwd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
passwd_test_getpwuid(struct passwd *pwd_model, void *mdata)
{
	struct passwd *pwd;

#ifdef DEBUG
	printf("testing getpwuid() with the following data...\n");
	dump_passwd(pwd_model);
#endif

	pwd = getpwuid(pwd_model->pw_uid);
	if ((passwd_test_correctness(pwd, NULL) != 0) ||
	    ((compare_passwd(pwd, pwd_model, NULL) != 0) &&
	    (passwd_check_ambiguity((struct passwd_test_data *)mdata, pwd)
	    != 0))) {
#ifdef DEBUG
		printf("not ok\n");
#endif
		return (-1);
	} else {
#ifdef DEBUG
		printf("ok\n");
#endif
		return (0);
	}
}