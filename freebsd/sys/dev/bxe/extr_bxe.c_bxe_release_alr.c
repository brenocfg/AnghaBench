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
 scalar_t__ GRCBASE_MCP ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bxe_release_alr(struct bxe_softc *sc)
{
    REG_WR(sc, GRCBASE_MCP + 0x9c, 0);
}