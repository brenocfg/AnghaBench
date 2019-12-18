#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* opts; } ;
typedef  TYPE_2__ tag_state ;
struct TYPE_4__ {int num_lines; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void print_list_lines(const char *message, const tag_state *state)
{
	const char *msg = message;
	int num = state->opts->num_lines - 1;

	if (!msg) return;

	/** first line - headline */
	while(*msg && *msg != '\n') printf("%c", *msg++);

	/** skip over new lines */
	while(*msg && *msg == '\n') msg++;

	printf("\n");

	/** print just headline? */
	if (num == 0) return;
	if (*msg && msg[1]) printf("\n");

	/** print individual commit/tag lines */
	while (*msg && num-- >= 2) {
		printf("    ");

		while (*msg && *msg != '\n') printf("%c", *msg++);

		/** handle consecutive new lines */
		if (*msg && *msg == '\n' && msg[1] == '\n') {
			num--;
			printf("\n");
		}
		while(*msg && *msg == '\n') msg++;

		printf("\n");
	}
}