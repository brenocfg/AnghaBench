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
struct ref_store {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 

__attribute__((used)) static int packed_copy_ref(struct ref_store *ref_store,
			   const char *oldrefname, const char *newrefname,
			   const char *logmsg)
{
	BUG("packed reference store does not support copying references");
}