#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ptunit_result {int dummy; } ;
struct TYPE_11__ {int limit; int /*<<< orphan*/  used; TYPE_2__* lru; } ;
struct iscache_fixture {TYPE_1__** section; TYPE_7__ iscache; } ;
struct TYPE_10__ {struct TYPE_10__* next; int /*<<< orphan*/  section; } ;
struct TYPE_9__ {int size; } ;

/* Variables and functions */
 int pt_iscache_add (TYPE_7__*,TYPE_1__*,int) ; 
 int pt_section_map (TYPE_1__*) ; 
 int pt_section_request_bcache (TYPE_1__*) ; 
 int pt_section_unmap (TYPE_1__*) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_int_gt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_null (TYPE_2__*) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (TYPE_2__*) ; 
 int /*<<< orphan*/  ptu_ptr_eq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ptunit_result lru_bcache_evict(struct iscache_fixture *cfix)
{
	int status, isid;

	cfix->iscache.limit = 4 * cfix->section[0]->size +
		cfix->section[1]->size - 1;
	ptu_uint_eq(cfix->iscache.used, 0ull);
	ptu_null(cfix->iscache.lru);

	isid = pt_iscache_add(&cfix->iscache, cfix->section[0], 0xa000ull);
	ptu_int_gt(isid, 0);

	isid = pt_iscache_add(&cfix->iscache, cfix->section[1], 0xa000ull);
	ptu_int_gt(isid, 0);

	status = pt_section_map(cfix->section[0]);
	ptu_int_eq(status, 0);

	status = pt_section_unmap(cfix->section[0]);
	ptu_int_eq(status, 0);

	status = pt_section_map(cfix->section[1]);
	ptu_int_eq(status, 0);

	status = pt_section_unmap(cfix->section[1]);
	ptu_int_eq(status, 0);

	status = pt_section_request_bcache(cfix->section[0]);
	ptu_int_eq(status, 0);

	ptu_ptr(cfix->iscache.lru);
	ptu_ptr_eq(cfix->iscache.lru->section, cfix->section[0]);
	ptu_null(cfix->iscache.lru->next);
	ptu_uint_eq(cfix->iscache.used, 4 * cfix->section[0]->size);

	return ptu_passed();
}