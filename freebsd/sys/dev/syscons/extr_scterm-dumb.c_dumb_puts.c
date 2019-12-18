#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_7__ {TYPE_1__* sc; } ;
typedef  TYPE_2__ scr_stat ;
struct TYPE_6__ {int /*<<< orphan*/  write_in_progress; int /*<<< orphan*/ * scr_map; } ;

/* Variables and functions */
 int SC_NORM_ATTR ; 
 int /*<<< orphan*/  sc_term_gen_print (TYPE_2__*,int /*<<< orphan*/ **,int*,int) ; 
 int /*<<< orphan*/  sc_term_gen_scroll (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
dumb_puts(scr_stat *scp, u_char *buf, int len)
{
	while (len > 0) {
		++scp->sc->write_in_progress;
		sc_term_gen_print(scp, &buf, &len, SC_NORM_ATTR << 8);
    		sc_term_gen_scroll(scp, scp->sc->scr_map[0x20],
				   SC_NORM_ATTR << 8);
		--scp->sc->write_in_progress;
	}
}