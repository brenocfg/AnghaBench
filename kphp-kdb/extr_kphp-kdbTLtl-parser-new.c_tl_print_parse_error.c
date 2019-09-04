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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,char*) ; 
 char* last_error ; 
 int last_error_line ; 
 int last_error_line_pos ; 
 int /*<<< orphan*/  stderr ; 

void tl_print_parse_error (void) {
  fprintf (stderr, "Error near line %d pos %d: `%s`\n", last_error_line + 1, last_error_line_pos + 1, last_error);
}