#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t wint_t ;
typedef  size_t wchar_t ;
typedef  int /*<<< orphan*/  unparsbuf ;
typedef  int /*<<< orphan*/  extrabuf ;
struct TYPE_6__ {scalar_t__ func; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ el_bindings_t ;
typedef  scalar_t__ el_action_t ;
struct TYPE_5__ {size_t nfunc; scalar_t__* key; int* alt; TYPE_2__* help; } ;
struct TYPE_7__ {int /*<<< orphan*/  el_errfile; TYPE_1__ el_map; int /*<<< orphan*/  el_outfile; } ;
typedef  TYPE_3__ EditLine ;

/* Variables and functions */
 scalar_t__ ED_UNASSIGNED ; 
 int /*<<< orphan*/  EL_ABORT (int /*<<< orphan*/ ) ; 
 int EL_BUFSIZ ; 
 int /*<<< orphan*/  STRQQ ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  keymacro__decode_str (size_t*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
map_print_some_keys(EditLine *el, el_action_t *map, wint_t first, wint_t last)
{
	el_bindings_t *bp, *ep;
	wchar_t firstbuf[2], lastbuf[2];
	char unparsbuf[EL_BUFSIZ], extrabuf[EL_BUFSIZ];

	firstbuf[0] = first;
	firstbuf[1] = 0;
	lastbuf[0] = last;
	lastbuf[1] = 0;
	if (map[first] == ED_UNASSIGNED) {
		if (first == last) {
			(void) keymacro__decode_str(firstbuf, unparsbuf,
			    sizeof(unparsbuf), STRQQ);
			(void) fprintf(el->el_outfile,
			    "%-15s->  is undefined\n", unparsbuf);
		}
		return;
	}
	ep = &el->el_map.help[el->el_map.nfunc];
	for (bp = el->el_map.help; bp < ep; bp++) {
		if (bp->func == map[first]) {
			if (first == last) {
				(void) keymacro__decode_str(firstbuf, unparsbuf,
				    sizeof(unparsbuf), STRQQ);
				(void) fprintf(el->el_outfile, "%-15s->  %ls\n",
				    unparsbuf, bp->name);
			} else {
				(void) keymacro__decode_str(firstbuf, unparsbuf,
				    sizeof(unparsbuf), STRQQ);
				(void) keymacro__decode_str(lastbuf, extrabuf,
				    sizeof(extrabuf), STRQQ);
				(void) fprintf(el->el_outfile,
				    "%-4s to %-7s->  %ls\n",
				    unparsbuf, extrabuf, bp->name);
			}
			return;
		}
	}
#ifdef MAP_DEBUG
	if (map == el->el_map.key) {
		(void) keymacro__decode_str(firstbuf, unparsbuf,
		    sizeof(unparsbuf), STRQQ);
		(void) fprintf(el->el_outfile,
		    "BUG!!! %s isn't bound to anything.\n", unparsbuf);
		(void) fprintf(el->el_outfile, "el->el_map.key[%d] == %d\n",
		    first, el->el_map.key[first]);
	} else {
		(void) keymacro__decode_str(firstbuf, unparsbuf,
		    sizeof(unparsbuf), STRQQ);
		(void) fprintf(el->el_outfile,
		    "BUG!!! %s isn't bound to anything.\n", unparsbuf);
		(void) fprintf(el->el_outfile, "el->el_map.alt[%d] == %d\n",
		    first, el->el_map.alt[first]);
	}
#endif
	EL_ABORT((el->el_errfile, "Error printing keys\n"));
}