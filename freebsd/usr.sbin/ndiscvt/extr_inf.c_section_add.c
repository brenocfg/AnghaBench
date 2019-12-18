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
struct section {char const* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct section*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct section*,int) ; 
 int /*<<< orphan*/  link ; 
 struct section* malloc (int) ; 
 int /*<<< orphan*/  sh ; 

void
section_add (const char *s)
{
	struct section *sec;

	sec = malloc(sizeof(struct section));
	bzero(sec, sizeof(struct section));
	sec->name = s;
	TAILQ_INSERT_TAIL(&sh, sec, link);

	return;
}