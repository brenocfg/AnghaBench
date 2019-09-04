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
 int files_copy_or_rename_ref (struct ref_store*,char const*,char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int files_rename_ref(struct ref_store *ref_store,
			    const char *oldrefname, const char *newrefname,
			    const char *logmsg)
{
	return files_copy_or_rename_ref(ref_store, oldrefname,
				 newrefname, logmsg, 0);
}