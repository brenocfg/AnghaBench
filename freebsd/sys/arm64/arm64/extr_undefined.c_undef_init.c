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

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdb_trapper ; 
 int /*<<< orphan*/  id_aa64mmfr2_handler ; 
 int /*<<< orphan*/  install_undef_handler (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * undef_handlers ; 

void
undef_init(void)
{

	LIST_INIT(&undef_handlers[0]);
	LIST_INIT(&undef_handlers[1]);

	install_undef_handler(false, id_aa64mmfr2_handler);
#ifdef COMPAT_FREEBSD32
	install_undef_handler(true, gdb_trapper);
#endif
}