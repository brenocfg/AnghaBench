#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  outbuf ;
struct TYPE_7__ {scalar_t__ func; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ el_bindings_t ;
typedef  scalar_t__ el_action_t ;
struct TYPE_6__ {size_t nfunc; TYPE_2__* help; } ;
struct TYPE_8__ {int /*<<< orphan*/  el_outfile; TYPE_1__ el_map; } ;
typedef  TYPE_3__ EditLine ;

/* Variables and functions */
 int EL_BUFSIZ ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keymacro__decode_str (char const*,char*,int,char*) ; 
 int /*<<< orphan*/  keymacro_print (TYPE_3__*,char const*) ; 

__attribute__((used)) static void
map_print_key(EditLine *el, el_action_t *map, const wchar_t *in)
{
	char outbuf[EL_BUFSIZ];
	el_bindings_t *bp, *ep;

	if (in[0] == '\0' || in[1] == '\0') {
		(void) keymacro__decode_str(in, outbuf, sizeof(outbuf), "");
		ep = &el->el_map.help[el->el_map.nfunc];
		for (bp = el->el_map.help; bp < ep; bp++)
			if (bp->func == map[(unsigned char) *in]) {
				(void) fprintf(el->el_outfile,
				    "%s\t->\t%ls\n", outbuf, bp->name);
				return;
			}
	} else
		keymacro_print(el, in);
}