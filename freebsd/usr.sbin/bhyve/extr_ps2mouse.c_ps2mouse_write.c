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
typedef  int uint8_t ;
struct ps2mouse_softc {int curcmd; int sampling_rate; int resolution; int status; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int PS2MC_ACK ; 
 int PS2MC_BAT_SUCCESS ; 
#define  PS2MC_DISABLE 140 
#define  PS2MC_ENABLE 139 
#define  PS2MC_RESET_DEV 138 
#define  PS2MC_SEND_DEV_DATA 137 
#define  PS2MC_SEND_DEV_ID 136 
#define  PS2MC_SEND_DEV_STATUS 135 
#define  PS2MC_SET_DEFAULTS 134 
#define  PS2MC_SET_REMOTE_MODE 133 
#define  PS2MC_SET_RESOLUTION 132 
#define  PS2MC_SET_SAMPLING_RATE 131 
#define  PS2MC_SET_SCALING1 130 
#define  PS2MC_SET_SCALING2 129 
#define  PS2MC_SET_STREAM_MODE 128 
 int PS2MOUSE_DEV_ID ; 
 int PS2M_STS_ENABLE_DEV ; 
 int PS2M_STS_REMOTE_MODE ; 
 int /*<<< orphan*/  fifo_put (struct ps2mouse_softc*,int) ; 
 int /*<<< orphan*/  fifo_reset (struct ps2mouse_softc*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  movement_get (struct ps2mouse_softc*) ; 
 int /*<<< orphan*/  ps2mouse_reset (struct ps2mouse_softc*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

void
ps2mouse_write(struct ps2mouse_softc *sc, uint8_t val, int insert)
{
	pthread_mutex_lock(&sc->mtx);
	fifo_reset(sc);
	if (sc->curcmd) {
		switch (sc->curcmd) {
		case PS2MC_SET_SAMPLING_RATE:
			sc->sampling_rate = val;
			fifo_put(sc, PS2MC_ACK);
			break;
		case PS2MC_SET_RESOLUTION:
			sc->resolution = val;
			fifo_put(sc, PS2MC_ACK);
			break;
		default:
			fprintf(stderr, "Unhandled ps2 mouse current "
			    "command byte 0x%02x\n", val);
			break;
		}
		sc->curcmd = 0;

	} else if (insert) {
		fifo_put(sc, val);
	} else {
		switch (val) {
		case 0x00:
			fifo_put(sc, PS2MC_ACK);
			break;
		case PS2MC_RESET_DEV:
			ps2mouse_reset(sc);
			fifo_put(sc, PS2MC_ACK);
			fifo_put(sc, PS2MC_BAT_SUCCESS);
			fifo_put(sc, PS2MOUSE_DEV_ID);
			break;
		case PS2MC_SET_DEFAULTS:
			ps2mouse_reset(sc);
			fifo_put(sc, PS2MC_ACK);
			break;
		case PS2MC_DISABLE:
			fifo_reset(sc);
			sc->status &= ~PS2M_STS_ENABLE_DEV;
			fifo_put(sc, PS2MC_ACK);
			break;
		case PS2MC_ENABLE:
			fifo_reset(sc);
			sc->status |= PS2M_STS_ENABLE_DEV;
			fifo_put(sc, PS2MC_ACK);
			break;
		case PS2MC_SET_SAMPLING_RATE:
			sc->curcmd = val;
			fifo_put(sc, PS2MC_ACK);
			break;
		case PS2MC_SEND_DEV_ID:
			fifo_put(sc, PS2MC_ACK);
			fifo_put(sc, PS2MOUSE_DEV_ID);
			break;
		case PS2MC_SET_REMOTE_MODE:
			sc->status |= PS2M_STS_REMOTE_MODE;
			fifo_put(sc, PS2MC_ACK);
			break;
		case PS2MC_SEND_DEV_DATA:
			fifo_put(sc, PS2MC_ACK);
			movement_get(sc);
			break;
		case PS2MC_SET_STREAM_MODE:
			sc->status &= ~PS2M_STS_REMOTE_MODE;
			fifo_put(sc, PS2MC_ACK);
			break;
		case PS2MC_SEND_DEV_STATUS:
			fifo_put(sc, PS2MC_ACK);
			fifo_put(sc, sc->status);
			fifo_put(sc, sc->resolution);
			fifo_put(sc, sc->sampling_rate);
			break;
		case PS2MC_SET_RESOLUTION:
			sc->curcmd = val;
			fifo_put(sc, PS2MC_ACK);
			break;
		case PS2MC_SET_SCALING1:
		case PS2MC_SET_SCALING2:
			fifo_put(sc, PS2MC_ACK);
			break;
		default:
			fifo_put(sc, PS2MC_ACK);
			fprintf(stderr, "Unhandled ps2 mouse command "
			    "0x%02x\n", val);
			break;
		}
	}
	pthread_mutex_unlock(&sc->mtx);
}