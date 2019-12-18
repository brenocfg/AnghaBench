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
struct tty {int dummy; } ;
typedef  TYPE_1__* sc_p ;
struct TYPE_3__ {size_t outqlen; } ;

/* Variables and functions */
 TYPE_1__* ttyhook_softc (struct tty*) ; 

__attribute__((used)) static size_t
ngt_getc_poll(struct tty *tp)
{
	sc_p sc = ttyhook_softc(tp);

	return (sc->outqlen);
}