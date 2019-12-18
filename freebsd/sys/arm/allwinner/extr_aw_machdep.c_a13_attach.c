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
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALLWINNERSOC_A13 ; 
 int /*<<< orphan*/  ALLWINNERSOC_SUN5I ; 
 int /*<<< orphan*/  soc_family ; 
 int /*<<< orphan*/  soc_type ; 

__attribute__((used)) static int
a13_attach(platform_t plat)
{
	soc_type = ALLWINNERSOC_A13;
	soc_family = ALLWINNERSOC_SUN5I;
	return (0);
}