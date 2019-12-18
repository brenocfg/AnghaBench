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
struct TYPE_4__ {char* name; int /*<<< orphan*/  stype; int /*<<< orphan*/  gen_name; } ;
typedef  TYPE_1__ Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  SUndefined ; 
 scalar_t__ emalloc (int) ; 
 int /*<<< orphan*/  estrdup (char*) ; 
 int /*<<< orphan*/  hashtabadd (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ hashtabsearch (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  htab ; 
 int /*<<< orphan*/  output_name (int /*<<< orphan*/ ) ; 

Symbol *
addsym(char *name)
{
    Symbol key, *s;

    key.name = name;
    s = (Symbol *) hashtabsearch(htab, (void *) &key);
    if (s == NULL) {
	s = (Symbol *) emalloc(sizeof(*s));
	s->name = name;
	s->gen_name = estrdup(name);
	output_name(s->gen_name);
	s->stype = SUndefined;
	hashtabadd(htab, s);
    }
    return s;
}