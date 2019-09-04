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
 int REF_ISSYMREF ; 
 int /*<<< orphan*/  resolve_ref_unsafe (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int ignore_symref_update(const char *refname)
{
	int flag;

	if (!resolve_ref_unsafe(refname, 0, NULL, &flag))
		return 0; /* non-existing refs are OK */
	return (flag & REF_ISSYMREF);
}