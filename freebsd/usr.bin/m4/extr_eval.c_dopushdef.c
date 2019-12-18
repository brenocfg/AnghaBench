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
 int /*<<< orphan*/  m4errx (int,char*) ; 
 int /*<<< orphan*/  macro_pushdef (char const*,char const*) ; 
 int /*<<< orphan*/  mimic_gnu ; 

__attribute__((used)) static void
dopushdef(const char *name, const char *defn)
{
	if (!*name && !mimic_gnu)
		m4errx(1, "null definition.");
	else
		macro_pushdef(name, defn);
}