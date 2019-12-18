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
 int /*<<< orphan*/  pt_iscache_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* pt_iscache_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptu_null (char const*) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result name_none(struct iscache_fixture *cfix)
{
	const char *name;

	pt_iscache_init(&cfix->iscache, NULL);

	name = pt_iscache_name(&cfix->iscache);
	ptu_null(name);

	return ptu_passed();
}