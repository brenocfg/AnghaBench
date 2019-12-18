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
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  variables_set ; 
 char* xmemdupz (char const*,size_t) ; 

__attribute__((used)) static void
note_variable (const char *var_ptr, size_t var_len)
{
  char *string = xmemdupz (var_ptr, var_len);

  string_list_append (&variables_set, string);
}