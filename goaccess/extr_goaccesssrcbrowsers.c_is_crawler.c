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
 int BROWSER_TYPE_LEN ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* verify_browser (char*,char*) ; 
 char* xstrdup (char const*) ; 

int
is_crawler (const char *agent)
{
  char type[BROWSER_TYPE_LEN];
  char *browser, *a;

  if (agent == NULL || *agent == '\0')
    return 0;

  if ((a = xstrdup (agent), browser = verify_browser (a, type)) != NULL)
    free (browser);
  free (a);

  return strcmp (type, "Crawlers") == 0 ? 1 : 0;
}