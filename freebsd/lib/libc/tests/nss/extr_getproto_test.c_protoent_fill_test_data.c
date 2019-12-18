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
 int /*<<< orphan*/  TEST_DATA_APPEND (int /*<<< orphan*/ ,struct protoent_test_data*,struct protoent*) ; 
 int /*<<< orphan*/  endprotoent () ; 
 struct protoent* getprotoent () ; 
 int /*<<< orphan*/  protoent ; 
 scalar_t__ protoent_test_correctness (struct protoent*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setprotoent (int) ; 

__attribute__((used)) static int
protoent_fill_test_data(struct protoent_test_data *td)
{
	struct protoent *pe;

	setprotoent(1);
	while ((pe = getprotoent()) != NULL) {
		if (protoent_test_correctness(pe, NULL) == 0)
			TEST_DATA_APPEND(protoent, td, pe);
		else
			return (-1);
	}
	endprotoent();

	return (0);
}