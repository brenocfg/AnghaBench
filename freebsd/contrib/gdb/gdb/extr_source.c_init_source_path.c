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
 int DIRNAME_SEPARATOR ; 
 int /*<<< orphan*/  forget_cached_source_info () ; 
 int /*<<< orphan*/  source_path ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

void
init_source_path (void)
{
  char buf[20];

  sprintf (buf, "$cdir%c$cwd", DIRNAME_SEPARATOR);
  source_path = xstrdup (buf);
  forget_cached_source_info ();
}