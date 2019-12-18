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
 int /*<<< orphan*/  debug_key (char const*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  verbosity ; 

void debug_error (const char *szAction, const char *szMsg, const char *key, int len) {
  if (!verbosity) { return; }
  fprintf (stderr, "Bad %s (key=\"", szAction);
  debug_key (key, len);
  fprintf (stderr, "\"); %s\n", szMsg);
}