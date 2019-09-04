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
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 

__attribute__((used)) static const char *
extract_protocol (const char *token)
{
  const char *lookfor;

  if ((lookfor = "HTTP/1.0", !strncmp (token, lookfor, 8)) ||
      (lookfor = "HTTP/1.1", !strncmp (token, lookfor, 8)) ||
      (lookfor = "HTTP/2", !strncmp (token, lookfor, 6)))
    return lookfor;
  return NULL;
}