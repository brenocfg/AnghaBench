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
 int /*<<< orphan*/  hast_index ; 
 int /*<<< orphan*/  module ; 
 int /*<<< orphan*/  oid_hast ; 
 int /*<<< orphan*/  or_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hast_start(void)
{
	hast_index = or_register(&oid_hast,
	    "The MIB module for BEGEMOT-HAST-MIB.", module);
}