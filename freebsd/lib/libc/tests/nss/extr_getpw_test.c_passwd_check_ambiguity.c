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
 int /*<<< orphan*/ * TEST_DATA_FIND (int /*<<< orphan*/ ,struct passwd_test_data*,struct passwd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compare_passwd ; 
 int /*<<< orphan*/  passwd ; 

__attribute__((used)) static int
passwd_check_ambiguity(struct passwd_test_data *td, struct passwd *pwd)
{

	return (TEST_DATA_FIND(passwd, td, pwd, compare_passwd,
		NULL) != NULL ? 0 : -1);
}