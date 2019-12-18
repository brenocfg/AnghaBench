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
typedef  int /*<<< orphan*/  ndptr ;

/* Variables and functions */
 int /*<<< orphan*/  macros ; 
 int /*<<< orphan*/  ohash_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohash_qlookup (int /*<<< orphan*/ *,char const*) ; 

ndptr
lookup(const char *name)
{
	return ohash_find(&macros, ohash_qlookup(&macros, name));
}