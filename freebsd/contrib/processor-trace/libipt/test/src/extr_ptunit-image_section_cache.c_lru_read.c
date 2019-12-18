#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct ptunit_result {int dummy; } ;
struct TYPE_9__ {unsigned long long limit; int /*<<< orphan*/  used; TYPE_2__* lru; } ;
struct iscache_fixture {TYPE_1__** section; TYPE_4__ iscache; } ;
struct TYPE_8__ {struct TYPE_8__* next; int /*<<< orphan*/  section; } ;
struct TYPE_7__ {unsigned long long size; } ;

/* Variables and functions */
 int pt_iscache_add (TYPE_4__*,TYPE_1__*,int) ; 
 int pt_iscache_read (TYPE_4__*,int*,unsigned long long,int,int) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 int /*<<< orphan*/  ptu_int_gt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_null (TYPE_2__*) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (TYPE_2__*) ; 
 int /*<<< orphan*/  ptu_ptr_eq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static struct ptunit_result lru_read(struct iscache_fixture *cfix)
{
	uint8_t buffer[] = { 0xcc, 0xcc, 0xcc };
	int status, isid;

	cfix->iscache.limit = cfix->section[0]->size;
	ptu_uint_eq(cfix->iscache.used, 0ull);
	ptu_null(cfix->iscache.lru);

	isid = pt_iscache_add(&cfix->iscache, cfix->section[0], 0xa000ull);
	ptu_int_gt(isid, 0);

	status = pt_iscache_read(&cfix->iscache, buffer, 2ull, isid, 0xa008ull);
	ptu_int_eq(status, 2);

	ptu_ptr(cfix->iscache.lru);
	ptu_ptr_eq(cfix->iscache.lru->section, cfix->section[0]);
	ptu_null(cfix->iscache.lru->next);
	ptu_uint_eq(cfix->iscache.used, cfix->section[0]->size);

	return ptu_passed();
}