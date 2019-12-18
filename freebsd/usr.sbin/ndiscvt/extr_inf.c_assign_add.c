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
struct assign {void** vals; void* key; int /*<<< orphan*/  section; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct assign*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ah ; 
 int /*<<< orphan*/  bzero (struct assign*,int) ; 
 int /*<<< orphan*/  clear_words () ; 
 int idx ; 
 int /*<<< orphan*/  link ; 
 struct assign* malloc (int) ; 
 int /*<<< orphan*/  section_head ; 
 int /*<<< orphan*/  sh ; 
 void* sstrdup (char const*) ; 
 char const** words ; 

void
assign_add (const char *a)
{
	struct assign *assign;
	int i;

	assign = malloc(sizeof(struct assign));
	bzero(assign, sizeof(struct assign));
	assign->section = TAILQ_LAST(&sh, section_head);
	assign->key = sstrdup(a);
	for (i = 0; i < idx; i++)
		assign->vals[(idx - 1) - i] = sstrdup(words[i]);
	TAILQ_INSERT_TAIL(&ah, assign, link);

	clear_words();
	return;
}