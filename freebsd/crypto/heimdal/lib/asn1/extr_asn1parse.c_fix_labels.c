#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/  gen_name; } ;
typedef  TYPE_1__ Symbol ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fix_labels2 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static void
fix_labels(Symbol *s)
{
    char *p = NULL;
    if (asprintf(&p, "choice_%s", s->gen_name) < 0 || p == NULL)
	errx(1, "malloc");
    fix_labels2(s->type, p);
    free(p);
}