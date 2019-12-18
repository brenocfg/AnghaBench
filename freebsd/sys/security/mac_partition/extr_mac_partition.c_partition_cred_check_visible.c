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
struct ucred {int /*<<< orphan*/  cr_label; } ;

/* Variables and functions */
 int ESRCH ; 
 int partition_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
partition_cred_check_visible(struct ucred *cr1, struct ucred *cr2)
{
	int error;

	error = partition_check(cr1->cr_label, cr2->cr_label);

	return (error == 0 ? 0 : ESRCH);
}