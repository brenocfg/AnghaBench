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
typedef  enum color_clean { ____Placeholder_color_clean } color_clean ;

/* Variables and functions */
 char* clean_get_color (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void clean_print_color(enum color_clean ix)
{
	printf("%s", clean_get_color(ix));
}