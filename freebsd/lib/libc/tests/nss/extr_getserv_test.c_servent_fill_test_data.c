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
 int /*<<< orphan*/  TEST_DATA_APPEND (int /*<<< orphan*/ ,struct servent_test_data*,struct servent*) ; 
 int /*<<< orphan*/  endservent () ; 
 struct servent* getservent () ; 
 int /*<<< orphan*/  servent ; 
 scalar_t__ servent_test_correctness (struct servent*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setservent (int) ; 

__attribute__((used)) static int
servent_fill_test_data(struct servent_test_data *td)
{
	struct servent *serv;

	setservent(1);
	while ((serv = getservent()) != NULL) {
		if (servent_test_correctness(serv, NULL) == 0)
			TEST_DATA_APPEND(servent, td, serv);
		else
			return (-1);
	}
	endservent();

	return (0);
}