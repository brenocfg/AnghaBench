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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int get_color_number (char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
set_normal_colors(int argc, char **argv, int *_index)
{
	int color;

	if (*_index < argc && (color = get_color_number(argv[*_index])) != -1) {
		(*_index)++;
		fprintf(stderr, "\033[=%dF", color);
		if (*_index < argc
		    && (color = get_color_number(argv[*_index])) != -1) {
			(*_index)++;
			fprintf(stderr, "\033[=%dG", color);
		}
	}
}