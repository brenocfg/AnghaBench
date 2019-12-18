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
struct sc_info {scalar_t__ cbuf; } ;

/* Variables and functions */
 int PCMDIR_PLAY ; 
 int PCMDIR_REC ; 
 int* coefficientSizes ; 
 int /*<<< orphan*/ * coefficients ; 
 int /*<<< orphan*/  nm_wr (struct sc_info*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  nm_wrbuf (struct sc_info*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nm_loadcoeff(struct sc_info *sc, int dir, int num)
{
	int ofs, sz, i;
	u_int32_t addr;

	addr = (dir == PCMDIR_PLAY)? 0x01c : 0x21c;
	if (dir == PCMDIR_REC)
		num += 8;
	sz = coefficientSizes[num];
	ofs = 0;
	while (num-- > 0)
		ofs+= coefficientSizes[num];
	for (i = 0; i < sz; i++)
		nm_wrbuf(sc, sc->cbuf + i, coefficients[ofs + i], 1);
	nm_wr(sc, addr, sc->cbuf, 4);
	if (dir == PCMDIR_PLAY)
		sz--;
	nm_wr(sc, addr + 4, sc->cbuf + sz, 4);
	return 0;
}