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
typedef  int uint64_t ;

/* Variables and functions */
 int pf_sep ; 
 int /*<<< orphan*/  printf (char*,int,char const*) ; 

__attribute__((used)) static void
printflag(uint64_t var, uint64_t mask, const char *name)
{

	if (var & mask) {
		printf("%c%s", pf_sep, name);
		pf_sep = ',';
	}
}