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
struct passwd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_DATA_APPEND (int /*<<< orphan*/ ,struct passwd_test_data*,struct passwd*) ; 
 int /*<<< orphan*/  endpwent () ; 
 struct passwd* getpwent () ; 
 int /*<<< orphan*/  passwd ; 
 scalar_t__ passwd_test_correctness (struct passwd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setpassent (int) ; 

__attribute__((used)) static int
passwd_fill_test_data(struct passwd_test_data *td)
{
	struct passwd *pwd;

	setpassent(1);
	while ((pwd = getpwent()) != NULL) {
		if (passwd_test_correctness(pwd, NULL) == 0)
			TEST_DATA_APPEND(passwd, td, pwd);
		else
			return (-1);
	}
	endpwent();

	return (0);
}