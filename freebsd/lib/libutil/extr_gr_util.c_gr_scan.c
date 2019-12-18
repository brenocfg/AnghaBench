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
struct group {char* gr_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  __gr_scan (char*,struct group*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct group* gr_dup (struct group*) ; 
 char* strdup (char const*) ; 

struct group *
gr_scan(const char *line)
{
	struct group gr;
	char *line_copy;
	struct group *new_gr;

	if ((line_copy = strdup(line)) == NULL)
		return (NULL);
	if (!__gr_scan(line_copy, &gr)) {
		free(line_copy);
		return (NULL);
	}
	new_gr = gr_dup(&gr);
	free(line_copy);
	if (gr.gr_mem != NULL)
		free(gr.gr_mem);

	return (new_gr);
}