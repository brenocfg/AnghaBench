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
struct fstypelist {int dummy; } ;
struct entry {void* options; void* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct fstypelist*,struct entry*,int /*<<< orphan*/ ) ; 
 struct entry* emalloc (int) ; 
 int /*<<< orphan*/  entries ; 
 void* estrdup (char const*) ; 

__attribute__((used)) static void
addentry(struct fstypelist *list, const char *type, const char *opts)
{
	struct entry *e;

	e = emalloc(sizeof(struct entry));
	e->type = estrdup(type);
	e->options = estrdup(opts);
	TAILQ_INSERT_TAIL(list, e, entries);
}