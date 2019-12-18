#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cmdinfo {scalar_t__ ci_calls; int /*<<< orphan*/  ci_comm; } ;
typedef  int /*<<< orphan*/  c2 ;
typedef  int /*<<< orphan*/  c1 ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ DBT ;

/* Variables and functions */
 int cmp_comm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct cmdinfo*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
cmp_calls(const DBT *d1, const DBT *d2)
{
	struct cmdinfo c1, c2;

	memcpy(&c1, d1->data, sizeof(c1));
	memcpy(&c2, d2->data, sizeof(c2));

	if (c1.ci_calls < c2.ci_calls)
		return -1;
	else if (c1.ci_calls == c2.ci_calls)
		return (cmp_comm(c1.ci_comm, c2.ci_comm));
	else
		return 1;
}