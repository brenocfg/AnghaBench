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
 int const OPT_UNIT ; 
 int md_list (char const*,int const,char const*) ; 

__attribute__((used)) static int
md_query(const char *name, const int opt, const char *fflag)
{

	return (md_list(name, opt | OPT_UNIT, fflag));
}