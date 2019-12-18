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
 int /*<<< orphan*/  git__strcmp ; 
 int status_entry_cmp_base (void const*,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int status_entry_cmp(const void *a, const void *b)
{
	return status_entry_cmp_base(a, b, git__strcmp);
}