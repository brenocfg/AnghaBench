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
struct hdr_list {char* h_name; struct hdr_list* h_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 struct hdr_list* calloc (int,int) ; 
 scalar_t__ eq (char*,char*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct hdr_list* htab ; 
 char* ns (char const*) ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strrchr (char const*,char) ; 

void
remember(const char *file)
{
	char *s;
	struct hdr_list *hl;

	if ((s = strrchr(file, '/')) != NULL)
		s = ns(s + 1);
	else
		s = ns(file);

	if (strchr(s, '_') && strncmp(s, "opt_", 4) != 0) {
		free(s);
		return;
	}
	for (hl = htab; hl != NULL; hl = hl->h_next) {
		if (eq(s, hl->h_name)) {
			free(s);
			return;
		}
	}
	hl = calloc(1, sizeof(*hl));
	if (hl == NULL)
		err(EXIT_FAILURE, "calloc");
	hl->h_name = s;
	hl->h_next = htab;
	htab = hl;
}