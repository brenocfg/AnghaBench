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
 int TL_ERRNUM ; 
 scalar_t__ TL_ERROR ; 
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ strdup (char const*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,char const*) ; 

int tl_fetch_set_error (const char *s, int errnum) {
  assert (s);
  if (TL_ERROR) {
    return 0;
  }
  vkprintf (2, "Error %s\n", s);
  TL_ERROR = strdup (s);
  TL_ERRNUM = errnum;
  return 0;
}