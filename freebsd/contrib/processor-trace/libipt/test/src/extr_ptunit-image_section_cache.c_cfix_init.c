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
struct iscache_fixture {int /*<<< orphan*/  iscache; } ;

/* Variables and functions */
 int /*<<< orphan*/  dfix_init ; 
 int pt_iscache_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,struct iscache_fixture*) ; 

__attribute__((used)) static struct ptunit_result cfix_init(struct iscache_fixture *cfix)
{
	int errcode;

	ptu_test(dfix_init, cfix);

	errcode = pt_iscache_init(&cfix->iscache, NULL);
	ptu_int_eq(errcode, 0);

	return ptu_passed();
}