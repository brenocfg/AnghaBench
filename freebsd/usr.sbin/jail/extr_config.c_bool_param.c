#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cfparam {char const* name; int /*<<< orphan*/  val; } ;
struct TYPE_2__ {int /*<<< orphan*/  s; } ;

/* Variables and functions */
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfstrings ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 char* strrchr (char const*,char) ; 
 scalar_t__ strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int
bool_param(const struct cfparam *p)
{
	const char *cs;

	if (p == NULL)
		return 0;
	cs = strrchr(p->name, '.');
	return !strncmp(cs ? cs + 1 : p->name, "no", 2) ^
	    (TAILQ_EMPTY(&p->val) ||
	     !strcasecmp(TAILQ_LAST(&p->val, cfstrings)->s, "true") ||
	     (strtol(TAILQ_LAST(&p->val, cfstrings)->s, NULL, 10)));
}