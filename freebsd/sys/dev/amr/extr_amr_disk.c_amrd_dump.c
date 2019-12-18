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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct disk {scalar_t__ d_drv1; } ;
struct amrd_softc {int amrd_drive; scalar_t__ amrd_controller; } ;
struct amr_softc {int amr_drive; } ;
typedef  int off_t ;

/* Variables and functions */
 int AMR_BLKSIZE ; 
 int ENXIO ; 
 int amr_dump_blocks (struct amr_softc*,int,int,void*,int) ; 

__attribute__((used)) static int
amrd_dump(void *arg, void *virtual, vm_offset_t physical, off_t offset, size_t length)
{

    struct amrd_softc	*amrd_sc;
    struct amr_softc	*amr_sc;
    int			error;
    struct disk		*dp;

    dp = arg;
    amrd_sc = (struct amrd_softc *)dp->d_drv1;
    if (amrd_sc == NULL)
	return(ENXIO);
    amr_sc  = (struct amr_softc *)amrd_sc->amrd_controller;

    if (length > 0) {
	int	driveno = amrd_sc->amrd_drive - amr_sc->amr_drive;
	if ((error = amr_dump_blocks(amr_sc,driveno,offset / AMR_BLKSIZE ,(void *)virtual,(int) length / AMR_BLKSIZE  )) != 0)
	    	return(error);

    }
    return(0);
}