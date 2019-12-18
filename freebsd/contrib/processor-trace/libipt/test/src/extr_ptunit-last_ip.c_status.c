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
struct ptunit_result {int dummy; } ;
struct pt_last_ip {int have_ip; scalar_t__ suppressed; } ;

/* Variables and functions */
 int pt_last_ip_query (int /*<<< orphan*/ *,struct pt_last_ip*) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result status(void)
{
	struct pt_last_ip last_ip;
	int errcode;

	last_ip.have_ip = 1;
	last_ip.suppressed = 0;

	errcode = pt_last_ip_query(NULL, &last_ip);
	ptu_int_eq(errcode, 0);

	return ptu_passed();
}