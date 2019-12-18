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
struct octeon_cop2_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctxzone ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
octeon_cop2_init(void* dummy)
{
	printf("Create COP2 context zone\n");
	ctxzone = uma_zcreate("COP2 context",
	                        sizeof(struct octeon_cop2_state), 
				NULL, NULL, NULL, NULL, 8, 0);
}