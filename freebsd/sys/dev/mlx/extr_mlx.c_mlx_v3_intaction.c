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
struct mlx_softc {int /*<<< orphan*/  mlx_state; } ;

/* Variables and functions */
#define  MLX_INTACTION_DISABLE 129 
#define  MLX_INTACTION_ENABLE 128 
 int /*<<< orphan*/  MLX_IO_ASSERT_LOCKED (struct mlx_softc*) ; 
 int /*<<< orphan*/  MLX_STATE_INTEN ; 
 int /*<<< orphan*/  MLX_V3_PUT_IER (struct mlx_softc*,int) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static void
mlx_v3_intaction(struct mlx_softc *sc, int action)
{
    debug_called(1);
    MLX_IO_ASSERT_LOCKED(sc);

    switch(action) {
    case MLX_INTACTION_DISABLE:
	MLX_V3_PUT_IER(sc, 0);
	sc->mlx_state &= ~MLX_STATE_INTEN;
	break;
    case MLX_INTACTION_ENABLE:
	MLX_V3_PUT_IER(sc, 1);
	sc->mlx_state |= MLX_STATE_INTEN;
	break;
    }
}