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
struct argv_array {int dummy; } ;

/* Variables and functions */
 int COLOR_MAXLEN ; 
 char* GIT_COLOR_RESET ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char*) ; 
 int /*<<< orphan*/  color_parse_mem (char const*,int,char*) ; 
 char* strchrnul (char const*,char) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,int,char const*) ; 

__attribute__((used)) static void parse_graph_colors_config(struct argv_array *colors, const char *string)
{
	const char *end, *start;

	start = string;
	end = string + strlen(string);
	while (start < end) {
		const char *comma = strchrnul(start, ',');
		char color[COLOR_MAXLEN];

		if (!color_parse_mem(start, comma - start, color))
			argv_array_push(colors, color);
		else
			warning(_("ignore invalid color '%.*s' in log.graphColors"),
				(int)(comma - start), start);
		start = comma + 1;
	}
	argv_array_push(colors, GIT_COLOR_RESET);
}