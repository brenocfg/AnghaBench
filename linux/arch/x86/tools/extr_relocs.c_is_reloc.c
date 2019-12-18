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
typedef  enum symtype { ____Placeholder_symtype } symtype ;

/* Variables and functions */
 int /*<<< orphan*/  regexec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__* sym_regex ; 
 int /*<<< orphan*/ * sym_regex_c ; 

__attribute__((used)) static int is_reloc(enum symtype type, const char *sym_name)
{
	return sym_regex[type] &&
		!regexec(&sym_regex_c[type], sym_name, 0, NULL, 0);
}