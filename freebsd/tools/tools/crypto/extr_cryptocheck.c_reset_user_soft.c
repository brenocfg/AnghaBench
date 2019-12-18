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
typedef  int /*<<< orphan*/  off ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_SOFT_ALLOW ; 
 int /*<<< orphan*/  sysctlbyname (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void
reset_user_soft(void)
{
	int off = 0;
	sysctlbyname(CRYPT_SOFT_ALLOW, NULL, NULL, &off, sizeof(off));
}