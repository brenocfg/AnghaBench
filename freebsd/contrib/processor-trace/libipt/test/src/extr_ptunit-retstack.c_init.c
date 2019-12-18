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
struct pt_retstack {int dummy; } ;
typedef  int /*<<< orphan*/  retstack ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_retstack*,int,int) ; 
 int /*<<< orphan*/  pt_retstack_init (struct pt_retstack*) ; 
 int pt_retstack_is_empty (struct pt_retstack*) ; 
 int /*<<< orphan*/  ptu_int_ne (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result init(void)
{
	struct pt_retstack retstack;
	int status;

	memset(&retstack, 0xcd, sizeof(retstack));

	pt_retstack_init(&retstack);

	status = pt_retstack_is_empty(&retstack);
	ptu_int_ne(status, 0);

	return ptu_passed();
}