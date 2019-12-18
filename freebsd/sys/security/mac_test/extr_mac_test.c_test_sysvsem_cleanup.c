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
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_CHECK (struct label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_SYSV_SEM ; 
 int /*<<< orphan*/  sysvsem_cleanup ; 

__attribute__((used)) static void
test_sysvsem_cleanup(struct label *semalabel)
{

	LABEL_CHECK(semalabel, MAGIC_SYSV_SEM);
	COUNTER_INC(sysvsem_cleanup);
}