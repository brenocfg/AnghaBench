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
typedef  int u_long ;
struct usb_fifo {int dummy; } ;
struct ufm_softc {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOTTY ; 
#define  FM_GET_FREQ 132 
#define  FM_GET_STAT 131 
#define  FM_SET_FREQ 130 
#define  FM_START 129 
#define  FM_STOP 128 
 int FREAD ; 
 int FWRITE ; 
 int ufm_get_freq (struct ufm_softc*,void*) ; 
 int ufm_get_stat (struct ufm_softc*,void*) ; 
 int ufm_set_freq (struct ufm_softc*,void*) ; 
 int ufm_start (struct ufm_softc*,void*) ; 
 int ufm_stop (struct ufm_softc*,void*) ; 
 struct ufm_softc* usb_fifo_softc (struct usb_fifo*) ; 

__attribute__((used)) static int
ufm_ioctl(struct usb_fifo *fifo, u_long cmd, void *addr,
    int fflags)
{
	struct ufm_softc *sc = usb_fifo_softc(fifo);
	int error = 0;

	if ((fflags & (FWRITE | FREAD)) != (FWRITE | FREAD)) {
		return (EACCES);
	}

	switch (cmd) {
	case FM_SET_FREQ:
		error = ufm_set_freq(sc, addr);
		break;
	case FM_GET_FREQ:
		error = ufm_get_freq(sc, addr);
		break;
	case FM_START:
		error = ufm_start(sc, addr);
		break;
	case FM_STOP:
		error = ufm_stop(sc, addr);
		break;
	case FM_GET_STAT:
		error = ufm_get_stat(sc, addr);
		break;
	default:
		error = ENOTTY;
		break;
	}
	return (error);
}