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

__attribute__((used)) static void
find_variables (const char *string,
		void (*callback) (const char *var_ptr, size_t var_len))
{
  for (; *string != '\0';)
    if (*string++ == '$')
      {
	const char *variable_start;
	const char *variable_end;
	unsigned short int valid;
	char c;

	if (*string == '{')
	  string++;

	variable_start = string;
	c = *string;
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
	  {
	    do
	      c = *++string;
	    while ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		   || (c >= '0' && c <= '9') || c == '_');
	    variable_end = string;

	    if (variable_start[-1] == '{')
	      {
		if (*string == '}')
		  {
		    string++;
		    valid = 1;
		  }
		else
		  valid = 0;
	      }
	    else
	      valid = 1;

	    if (valid)
	      callback (variable_start, variable_end - variable_start);
	  }
      }
}