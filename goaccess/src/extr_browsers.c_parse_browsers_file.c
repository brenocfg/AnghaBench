#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int browsers_hash_idx; void* user_browsers_hash; int /*<<< orphan*/  browsers_file; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  FATAL (char*,...) ; 
 int MAX_CUSTOM_BROWSERS ; 
 int /*<<< orphan*/  MAX_LINE_BROWSERS ; 
 int /*<<< orphan*/ ** browsers ; 
 void* browsers_hash ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memmove (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_browser_token (void*,char*,int) ; 
 int /*<<< orphan*/  set_browser (void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 void* xmalloc (int) ; 

void
parse_browsers_file (void)
{
  char line[MAX_LINE_BROWSERS + 1];
  FILE *file;
  int n = 0;
  size_t i, len = ARRAY_SIZE (browsers);

  browsers_hash = xmalloc (ARRAY_SIZE (browsers) * sizeof (char **));
  /* load hash from the browser's array (default)  */
  for (i = 0; i < len; ++i) {
    set_browser (browsers_hash, i, browsers[i][0], browsers[i][1]);
  }

  if (!conf.browsers_file)
    return;

  /* could not open browsers file */
  if ((file = fopen (conf.browsers_file, "r")) == NULL)
    FATAL ("Unable to open browser's file: %s", strerror (errno));

  conf.user_browsers_hash = xmalloc (MAX_CUSTOM_BROWSERS * sizeof (char **));
  /* load hash from the user's given browsers file  */
  while (fgets (line, sizeof line, file) != NULL) {
    while (line[0] == ' ' || line[0] == '\t')
      memmove (line, line + 1, strlen (line));
    n++;

    if (line[0] == '\n' || line[0] == '\r' || line[0] == '#')
      continue;
    if (conf.browsers_hash_idx >= MAX_CUSTOM_BROWSERS)
      FATAL ("Maximum number of custom browsers has been reached");
    parse_browser_token (conf.user_browsers_hash, line, n);
  }
  fclose (file);
}