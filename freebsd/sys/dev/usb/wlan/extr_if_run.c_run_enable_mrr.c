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
struct run_softc {int dummy; } ;

/* Variables and functions */
 int CCK (int) ; 
 int OFDM (int) ; 
 int /*<<< orphan*/  RT2860_LG_FBK_CFG0 ; 
 int /*<<< orphan*/  RT2860_LG_FBK_CFG1 ; 
 int /*<<< orphan*/  run_write (struct run_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
run_enable_mrr(struct run_softc *sc)
{
#define	CCK(mcs)	(mcs)
#define	OFDM(mcs)	(1 << 3 | (mcs))
	run_write(sc, RT2860_LG_FBK_CFG0,
	    OFDM(6) << 28 |	/* 54->48 */
	    OFDM(5) << 24 |	/* 48->36 */
	    OFDM(4) << 20 |	/* 36->24 */
	    OFDM(3) << 16 |	/* 24->18 */
	    OFDM(2) << 12 |	/* 18->12 */
	    OFDM(1) <<  8 |	/* 12-> 9 */
	    OFDM(0) <<  4 |	/*  9-> 6 */
	    OFDM(0));		/*  6-> 6 */

	run_write(sc, RT2860_LG_FBK_CFG1,
	    CCK(2) << 12 |	/* 11->5.5 */
	    CCK(1) <<  8 |	/* 5.5-> 2 */
	    CCK(0) <<  4 |	/*   2-> 1 */
	    CCK(0));		/*   1-> 1 */
#undef OFDM
#undef CCK
}