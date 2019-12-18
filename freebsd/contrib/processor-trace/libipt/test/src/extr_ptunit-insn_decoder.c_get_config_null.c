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
struct pt_config {int dummy; } ;

/* Variables and functions */
 struct pt_config* pt_insn_get_config (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptu_null (struct pt_config const*) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result get_config_null(void)
{
	const struct pt_config *config;

	config = pt_insn_get_config(NULL);
	ptu_null(config);

	return ptu_passed();
}