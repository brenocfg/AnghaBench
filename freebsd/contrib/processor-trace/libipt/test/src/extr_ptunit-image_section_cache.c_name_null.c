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

/* Variables and functions */
 char* pt_iscache_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptu_null (char const*) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result name_null(void)
{
	const char *name;

	name = pt_iscache_name(NULL);
	ptu_null(name);

	return ptu_passed();
}