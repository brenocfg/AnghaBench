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
typedef  scalar_t__ svn_boolean_t ;

/* Variables and functions */
 scalar_t__ apr_tolower (char) ; 
 scalar_t__ apr_toupper (char) ; 

__attribute__((used)) static void convert_case(char *text, svn_boolean_t to_uppercase)
{
  char *c = text;
  while (*c)
    {
      *c = (char)(to_uppercase ? apr_toupper(*c) : apr_tolower(*c));
      ++c;
    }
}