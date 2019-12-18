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
 size_t lexleft ; 
 int /*<<< orphan*/  lexptr ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
looking_at (char const *s)
{
  size_t len;

  len = strlen(s);
  if (lexleft < len)
    return 0;
  return strncmp(s, lexptr, len) == 0;
}