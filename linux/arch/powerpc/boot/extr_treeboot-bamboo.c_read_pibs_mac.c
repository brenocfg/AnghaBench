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

/* Variables and functions */
 scalar_t__ PIBS_MAC0 ; 
 scalar_t__ PIBS_MAC1 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pibs_mac0 ; 
 int /*<<< orphan*/  pibs_mac1 ; 
 unsigned long long strtoull (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void read_pibs_mac(void)
{
	unsigned long long mac64;

	mac64 = strtoull((char *)PIBS_MAC0, 0, 16);
	memcpy(&pibs_mac0, (char *)&mac64+2, 6);

	mac64 = strtoull((char *)PIBS_MAC1, 0, 16);
	memcpy(&pibs_mac1, (char *)&mac64+2, 6);
}