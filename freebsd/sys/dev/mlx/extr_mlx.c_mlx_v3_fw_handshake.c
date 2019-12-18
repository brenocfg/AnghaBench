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
typedef  int u_int8_t ;
struct mlx_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int MLX_V3_FWERROR_PEND ; 
 int MLX_V3_GET_FWERROR (struct mlx_softc*) ; 
 int MLX_V3_GET_FWERROR_PARAM1 (struct mlx_softc*) ; 
 int MLX_V3_GET_FWERROR_PARAM2 (struct mlx_softc*) ; 
 int MLX_V3_GET_IDBR (struct mlx_softc*) ; 
 int MLX_V3_IDB_INIT_BUSY ; 
 int /*<<< orphan*/  MLX_V3_IDB_SACK ; 
 int /*<<< orphan*/  MLX_V3_PUT_FWERROR (struct mlx_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX_V3_PUT_IDBR (struct mlx_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static int 
mlx_v3_fw_handshake(struct mlx_softc *sc, int *error, int *param1, int *param2,
    int first)
{
    u_int8_t	fwerror;

    debug_called(2);

    /* first time around, clear any hardware completion status */
    if (first) {
	MLX_V3_PUT_IDBR(sc, MLX_V3_IDB_SACK);
	DELAY(1000);
    }

    /* init in progress? */
    if (!(MLX_V3_GET_IDBR(sc) & MLX_V3_IDB_INIT_BUSY))
	return(0);

    /* test error value */
    fwerror = MLX_V3_GET_FWERROR(sc);
    if (!(fwerror & MLX_V3_FWERROR_PEND))
	return(1);

    /* mask status pending bit, fetch status */
    *error = fwerror & ~MLX_V3_FWERROR_PEND;
    *param1 = MLX_V3_GET_FWERROR_PARAM1(sc);
    *param2 = MLX_V3_GET_FWERROR_PARAM2(sc);

    /* acknowledge */
    MLX_V3_PUT_FWERROR(sc, 0);

    return(2);
}