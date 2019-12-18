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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAMELLIA_FLS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAMELLIA_ROUNDSM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBL (int) ; 
 int /*<<< orphan*/  SUBR (int) ; 

void
camellia_encrypt256(const uint32_t *subkey, uint32_t *io)
{
    uint32_t il,ir,t0,t1;           /* temporary valiables */

    /* pre whitening but absorb kw2*/
    io[0] ^= SUBL(0);
    io[1] ^= SUBR(0);

    /* main iteration */
    CAMELLIA_ROUNDSM(io[0],io[1], SUBL(2),SUBR(2),
		     io[2],io[3],il,ir,t0,t1);
    CAMELLIA_ROUNDSM(io[2],io[3], SUBL(3),SUBR(3),
		     io[0],io[1],il,ir,t0,t1);
    CAMELLIA_ROUNDSM(io[0],io[1], SUBL(4),SUBR(4),
		     io[2],io[3],il,ir,t0,t1);
    CAMELLIA_ROUNDSM(io[2],io[3], SUBL(5),SUBR(5),
		     io[0],io[1],il,ir,t0,t1);
    CAMELLIA_ROUNDSM(io[0],io[1], SUBL(6),SUBR(6),
		     io[2],io[3],il,ir,t0,t1);
    CAMELLIA_ROUNDSM(io[2],io[3], SUBL(7),SUBR(7),
		     io[0],io[1],il,ir,t0,t1);

    CAMELLIA_FLS(io[0],io[1],io[2],io[3], SUBL(8),SUBR(8), SUBL(9),SUBR(9),
		 t0,t1,il,ir);

    CAMELLIA_ROUNDSM(io[0],io[1], SUBL(10),SUBR(10),
		     io[2],io[3],il,ir,t0,t1);
    CAMELLIA_ROUNDSM(io[2],io[3], SUBL(11),SUBR(11),
		     io[0],io[1],il,ir,t0,t1);
    CAMELLIA_ROUNDSM(io[0],io[1], SUBL(12),SUBR(12),
		     io[2],io[3],il,ir,t0,t1);
    CAMELLIA_ROUNDSM(io[2],io[3], SUBL(13),SUBR(13),
		     io[0],io[1],il,ir,t0,t1);
    CAMELLIA_ROUNDSM(io[0],io[1], SUBL(14),SUBR(14),
		     io[2],io[3],il,ir,t0,t1);
    CAMELLIA_ROUNDSM(io[2],io[3], SUBL(15),SUBR(15),
		     io[0],io[1],il,ir,t0,t1);

    CAMELLIA_FLS(io[0],io[1],io[2],io[3], SUBL(16),SUBR(16), SUBL(17),SUBR(17),
		 t0,t1,il,ir);

    CAMELLIA_ROUNDSM(io[0],io[1], SUBL(18),SUBR(18),
		     io[2],io[3],il,ir,t0,t1);
    CAMELLIA_ROUNDSM(io[2],io[3], SUBL(19),SUBR(19),
		     io[0],io[1],il,ir,t0,t1);
    CAMELLIA_ROUNDSM(io[0],io[1], SUBL(20),SUBR(20),
		     io[2],io[3],il,ir,t0,t1);
    CAMELLIA_ROUNDSM(io[2],io[3], SUBL(21),SUBR(21),
		     io[0],io[1],il,ir,t0,t1);
    CAMELLIA_ROUNDSM(io[0],io[1], SUBL(22),SUBR(22),
		     io[2],io[3],il,ir,t0,t1);
    CAMELLIA_ROUNDSM(io[2],io[3], SUBL(23),SUBR(23),
		     io[0],io[1],il,ir,t0,t1);

    CAMELLIA_FLS(io[0],io[1],io[2],io[3], SUBL(24),SUBR(24), SUBL(25),SUBR(25),
		 t0,t1,il,ir);

    CAMELLIA_ROUNDSM(io[0],io[1], SUBL(26),SUBR(26),
		     io[2],io[3],il,ir,t0,t1);
    CAMELLIA_ROUNDSM(io[2],io[3], SUBL(27),SUBR(27),
		     io[0],io[1],il,ir,t0,t1);
    CAMELLIA_ROUNDSM(io[0],io[1], SUBL(28),SUBR(28),
		     io[2],io[3],il,ir,t0,t1);
    CAMELLIA_ROUNDSM(io[2],io[3], SUBL(29),SUBR(29),
		     io[0],io[1],il,ir,t0,t1);
    CAMELLIA_ROUNDSM(io[0],io[1], SUBL(30),SUBR(30),
		     io[2],io[3],il,ir,t0,t1);
    CAMELLIA_ROUNDSM(io[2],io[3], SUBL(31),SUBR(31),
		     io[0],io[1],il,ir,t0,t1);

    /* post whitening but kw4 */
    io[2] ^= SUBL(32);
    io[3] ^= SUBR(32);

    t0 = io[0];
    t1 = io[1];
    io[0] = io[2];
    io[1] = io[3];
    io[2] = t0;
    io[3] = t1;
}