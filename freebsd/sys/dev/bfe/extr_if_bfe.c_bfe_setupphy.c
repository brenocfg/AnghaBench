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
typedef  int u_int32_t ;
struct bfe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfe_readphy (struct bfe_softc*,int,int*) ; 
 int /*<<< orphan*/  bfe_writephy (struct bfe_softc*,int,int) ; 

__attribute__((used)) static int
bfe_setupphy(struct bfe_softc *sc)
{
	u_int32_t val;

	/* Enable activity LED */
	bfe_readphy(sc, 26, &val);
	bfe_writephy(sc, 26, val & 0x7fff);
	bfe_readphy(sc, 26, &val);

	/* Enable traffic meter LED mode */
	bfe_readphy(sc, 27, &val);
	bfe_writephy(sc, 27, val | (1 << 6));

	return (0);
}