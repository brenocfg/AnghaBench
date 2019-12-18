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
 int /*<<< orphan*/  po_newdir ; 
 void* po_newdir_length ; 
 int /*<<< orphan*/  po_olddir ; 
 void* po_olddir_length ; 
 void* strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zstrdup (char const* const) ; 

void pending_operations_init (const char *const olddir_prefix, const char *const newdir_prefix) {
  po_olddir = zstrdup (olddir_prefix);
  po_newdir = zstrdup (newdir_prefix);
  po_olddir_length = strlen (po_olddir);
  po_newdir_length = strlen (po_newdir);
}