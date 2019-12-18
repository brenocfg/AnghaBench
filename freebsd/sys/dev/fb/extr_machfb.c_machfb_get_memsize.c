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
struct machfb_softc {int sc_flags; } ;

/* Variables and functions */
 int MACHFB_DSP ; 
 int /*<<< orphan*/  MEM_CNTL ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int regr (struct machfb_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
machfb_get_memsize(struct machfb_softc *sc)
{
	int tmp, memsize;
	const int mem_tab[] = {
		512, 1024, 2048, 4096, 6144, 8192, 12288, 16384
	};

	tmp = regr(sc, MEM_CNTL);
#ifdef MACHFB_DEBUG
	printf("memcntl=0x%08x\n", tmp);
#endif
	if (sc->sc_flags & MACHFB_DSP) {
		tmp &= 0x0000000f;
		if (tmp < 8)
			memsize = (tmp + 1) * 512;
		else if (tmp < 12)
			memsize = (tmp - 3) * 1024;
		else
			memsize = (tmp - 7) * 2048;
	} else
		memsize = mem_tab[tmp & 0x07];

	return (memsize);
}