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
 int /*<<< orphan*/  find_variables (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  note_variable ; 
 int /*<<< orphan*/  string_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_list_sort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  variables_set ; 

__attribute__((used)) static void
note_variables (const char *string)
{
  string_list_init (&variables_set);
  find_variables (string, &note_variable);
  string_list_sort (&variables_set);
}