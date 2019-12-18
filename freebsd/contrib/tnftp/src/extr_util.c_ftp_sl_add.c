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
typedef  int /*<<< orphan*/  StringList ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int sl_add (int /*<<< orphan*/ *,char*) ; 

void
ftp_sl_add(StringList *sl, char *i)
{

	if (sl_add(sl, i) == -1)
		err(1, "Unable to add `%s' to stringlist", i);
}