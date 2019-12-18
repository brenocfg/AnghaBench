#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* wchar_t ;
struct TYPE_7__ {void* wc; int /*<<< orphan*/ * ref; } ;
typedef  TYPE_1__ collchar_t ;

/* Variables and functions */
 int NUM_WT ; 
 TYPE_1__* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  collchars ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  new_pri () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static collchar_t *
get_collchar(wchar_t wc, int create)
{
	collchar_t	srch;
	collchar_t	*cc;
	int		i;

	srch.wc = wc;
	cc = RB_FIND(collchars, &collchars, &srch);
	if ((cc == NULL) && create) {
		if ((cc = calloc(1, sizeof(*cc))) == NULL) {
			fprintf(stderr, "out of memory");
			return (NULL);
		}
		for (i = 0; i < NUM_WT; i++) {
			cc->ref[i] = new_pri();
		}
		cc->wc = wc;
		RB_INSERT(collchars, &collchars, cc);
	}
	return (cc);
}