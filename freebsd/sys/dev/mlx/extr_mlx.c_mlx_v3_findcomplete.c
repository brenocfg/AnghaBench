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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct mlx_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_IO_ASSERT_LOCKED (struct mlx_softc*) ; 
 int MLX_V3_GET_ODBR (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_V3_GET_STATUS (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_V3_GET_STATUS_IDENT (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_V3_IDB_SACK ; 
 int MLX_V3_ODB_SAVAIL ; 
 int /*<<< orphan*/  MLX_V3_PUT_IDBR (struct mlx_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX_V3_PUT_ODBR (struct mlx_softc*,int) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static int
mlx_v3_findcomplete(struct mlx_softc *sc, u_int8_t *slot, u_int16_t *status)
{

    debug_called(2);
    MLX_IO_ASSERT_LOCKED(sc);

    /* status available? */
    if (MLX_V3_GET_ODBR(sc) & MLX_V3_ODB_SAVAIL) {
	*slot = MLX_V3_GET_STATUS_IDENT(sc);		/* get command identifier */
	*status = MLX_V3_GET_STATUS(sc);		/* get status */

	/* acknowledge completion */
	MLX_V3_PUT_ODBR(sc, MLX_V3_ODB_SAVAIL);
	MLX_V3_PUT_IDBR(sc, MLX_V3_IDB_SACK);
	return(1);
    }
    return(0);
}