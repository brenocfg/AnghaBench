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
 int /*<<< orphan*/  pt_iscache_init (int /*<<< orphan*/ *,char*) ; 
 char* pt_iscache_name (int /*<<< orphan*/ *) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_str_eq (char const*,char*) ; 

__attribute__((used)) static struct ptunit_result name(struct iscache_fixture *cfix)
{
	const char *name;

	pt_iscache_init(&cfix->iscache, "iscache-name");

	name = pt_iscache_name(&cfix->iscache);
	ptu_str_eq(name, "iscache-name");

	return ptu_passed();
}