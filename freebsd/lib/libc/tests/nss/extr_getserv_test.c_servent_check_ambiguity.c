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
struct servent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * TEST_DATA_FIND (int /*<<< orphan*/ ,struct servent_test_data*,struct servent*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compare_servent ; 
 int /*<<< orphan*/  servent ; 

__attribute__((used)) static int
servent_check_ambiguity(struct servent_test_data *td, struct servent *serv)
{

	return (TEST_DATA_FIND(servent, td, serv, compare_servent,
		NULL) != NULL ? 0 : -1);
}