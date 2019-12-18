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
struct vlist {int dummy; } ;

/* Variables and functions */
 int VAROBJ_TABLE_SIZE ; 
 int /*<<< orphan*/  add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_maintenance ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  var_zinteger ; 
 int /*<<< orphan*/  varobj_table ; 
 int /*<<< orphan*/  varobjdebug ; 
 int /*<<< orphan*/  xmalloc (int) ; 

void
_initialize_varobj (void)
{
  int sizeof_table = sizeof (struct vlist *) * VAROBJ_TABLE_SIZE;

  varobj_table = xmalloc (sizeof_table);
  memset (varobj_table, 0, sizeof_table);

  add_show_from_set (add_set_cmd ("debugvarobj", class_maintenance, var_zinteger, (char *) &varobjdebug, "Set varobj debugging.\n\
When non-zero, varobj debugging is enabled.", &setlist),
		     &showlist);
}