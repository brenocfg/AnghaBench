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
struct mlx_softc {int dummy; } ;
struct mlx_command {int /*<<< orphan*/ * mc_mailbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_IO_ASSERT_LOCKED (struct mlx_softc*) ; 
 int MLX_V5_GET_IDBR (struct mlx_softc*) ; 
 int MLX_V5_IDB_EMPTY ; 
 int /*<<< orphan*/  MLX_V5_IDB_HWMBOX_CMD ; 
 int /*<<< orphan*/  MLX_V5_PUT_IDBR (struct mlx_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX_V5_PUT_MAILBOX (struct mlx_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static int
mlx_v5_tryqueue(struct mlx_softc *sc, struct mlx_command *mc)
{
    int		i;

    debug_called(2);
    MLX_IO_ASSERT_LOCKED(sc);

    /* ready for our command? */
    if (MLX_V5_GET_IDBR(sc) & MLX_V5_IDB_EMPTY) {
	/* copy mailbox data to window */
	for (i = 0; i < 13; i++)
	    MLX_V5_PUT_MAILBOX(sc, i, mc->mc_mailbox[i]);

	/* post command */
	MLX_V5_PUT_IDBR(sc, MLX_V5_IDB_HWMBOX_CMD);
	return(1);
    }
    return(0);
}