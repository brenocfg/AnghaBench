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
struct ref {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int strcmp (void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmp_name_ref(const void *name, const void *ref)
{
	return strcmp(name, (*(struct ref **)ref)->name);
}