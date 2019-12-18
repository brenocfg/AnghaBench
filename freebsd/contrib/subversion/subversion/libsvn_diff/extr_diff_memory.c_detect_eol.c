#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ len; char* data; } ;
typedef  TYPE_1__ svn_string_t ;

/* Variables and functions */

__attribute__((used)) static const char *
detect_eol(svn_string_t *token)
{
  const char *curp;

  if (token->len == 0)
    return NULL;

  curp = token->data + token->len - 1;
  if (*curp == '\r')
    return "\r";
  else if (*curp != '\n')
    return NULL;
  else
    {
      if (token->len == 1
          || *(--curp) != '\r')
        return "\n";
      else
        return "\r\n";
    }
}