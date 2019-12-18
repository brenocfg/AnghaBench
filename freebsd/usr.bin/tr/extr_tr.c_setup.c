#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cset {int dummy; } ;
struct TYPE_4__ {char* str; int /*<<< orphan*/  lastch; } ;
typedef  TYPE_1__ STR ;

/* Variables and functions */
 int /*<<< orphan*/  cset_add (struct cset*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cset_addclass (struct cset*,int /*<<< orphan*/ ,int) ; 
 struct cset* cset_alloc () ; 
 int /*<<< orphan*/  cset_cache (struct cset*) ; 
 int /*<<< orphan*/  cset_invert (struct cset*) ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 scalar_t__ next (TYPE_1__*) ; 
 int /*<<< orphan*/  wctype (char*) ; 

__attribute__((used)) static struct cset *
setup(char *arg, STR *str, int cflag, int Cflag)
{
	struct cset *cs;

	cs = cset_alloc();
	if (cs == NULL)
		err(1, NULL);
	str->str = arg;
	while (next(str))
		cset_add(cs, str->lastch);
	if (Cflag)
		cset_addclass(cs, wctype("rune"), true);
	if (cflag || Cflag)
		cset_invert(cs);
	cset_cache(cs);
	return (cs);
}