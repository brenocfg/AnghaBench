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
struct ctl_be_block_softc {int /*<<< orphan*/  beio_zone; } ;
struct ctl_be_block_io {struct ctl_be_block_softc* softc; } ;

/* Variables and functions */
 int M_WAITOK ; 
 int M_ZERO ; 
 struct ctl_be_block_io* uma_zalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ctl_be_block_io *
ctl_alloc_beio(struct ctl_be_block_softc *softc)
{
	struct ctl_be_block_io *beio;

	beio = uma_zalloc(softc->beio_zone, M_WAITOK | M_ZERO);
	beio->softc = softc;
	return (beio);
}