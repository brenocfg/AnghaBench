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
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGI (struct bxe_softc*,char*,char*,char const*) ; 

__attribute__((used)) static void
bxe_print_next_block(struct bxe_softc *sc,
                     int              idx,
                     const char       *blk)
{
    BLOGI(sc, "%s%s", idx ? ", " : "", blk);
}