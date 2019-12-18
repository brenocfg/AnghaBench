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
struct protoent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * TEST_DATA_FIND (int /*<<< orphan*/ ,struct protoent_test_data*,struct protoent*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compare_protoent ; 
 int /*<<< orphan*/  protoent ; 

__attribute__((used)) static int
protoent_check_ambiguity(struct protoent_test_data *td, struct protoent *pe)
{

	return (TEST_DATA_FIND(protoent, td, pe, compare_protoent,
		NULL) != NULL ? 0 : -1);
}