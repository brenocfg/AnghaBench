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
 char* strchr (char*,char) ; 

__attribute__((used)) static void
strip_qstring (char *req)
{
  char *qmark;
  if ((qmark = strchr (req, '?')) != NULL) {
    if ((qmark - req) > 0)
      *qmark = '\0';
  }
}