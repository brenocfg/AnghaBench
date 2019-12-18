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
struct cap_rights_init_args {int /*<<< orphan*/  cria_value4; int /*<<< orphan*/  cria_value3; int /*<<< orphan*/  cria_value2; int /*<<< orphan*/  cria_value1; int /*<<< orphan*/ * cria_rights; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_RIGHTS_VERSION ; 
 int /*<<< orphan*/  __cap_rights_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 

void
__cap_rights_sysinit(void *arg)
{
	struct cap_rights_init_args *cria = arg;
	cap_rights_t *rights = cria->cria_rights;

	__cap_rights_init(CAP_RIGHTS_VERSION, rights, cria->cria_value1,
       cria->cria_value2, cria->cria_value3, cria->cria_value4, 0ULL);
}