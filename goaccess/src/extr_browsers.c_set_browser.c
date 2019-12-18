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
 char** xcalloc (int,int) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static void
set_browser (char ***list, int idx, const char *browser, const char *type)
{
  list[idx] = xcalloc (2, sizeof (char *));
  list[idx][0] = xstrdup (browser);
  list[idx][1] = xstrdup (type);
}