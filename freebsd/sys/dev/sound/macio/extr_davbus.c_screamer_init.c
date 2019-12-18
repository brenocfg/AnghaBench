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
struct snd_mixer {int dummy; } ;
struct davbus_softc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  reg; int /*<<< orphan*/  (* set_outputs ) (struct davbus_softc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* read_status ) (struct davbus_softc*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DAVBUS_CODEC_STATUS ; 
 int /*<<< orphan*/  SCREAMER_CODEC_ADDR0 ; 
 int /*<<< orphan*/  SCREAMER_CODEC_ADDR2 ; 
 int /*<<< orphan*/  SCREAMER_CODEC_ADDR4 ; 
 int /*<<< orphan*/  SCREAMER_CODEC_ADDR5 ; 
 int /*<<< orphan*/  SCREAMER_CODEC_ADDR6 ; 
 int SCREAMER_DEFAULT_CD_GAIN ; 
 int SCREAMER_INPUT_CD ; 
 int /*<<< orphan*/  SOUND_MASK_VOLUME ; 
 int /*<<< orphan*/  bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct davbus_softc* mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  mix_setdevs (struct snd_mixer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  screamer_read_status (struct davbus_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screamer_set_outputs (struct davbus_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screamer_write_locked (struct davbus_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
screamer_init(struct snd_mixer *m)
{
	struct davbus_softc *d;

	d = mix_getdevinfo(m);

	d->read_status = screamer_read_status;
	d->set_outputs = screamer_set_outputs;

	mtx_lock(&d->mutex);

	screamer_write_locked(d, SCREAMER_CODEC_ADDR0, SCREAMER_INPUT_CD | 
	    SCREAMER_DEFAULT_CD_GAIN);

	screamer_set_outputs(d, screamer_read_status(d, 
	    bus_read_4(d->reg, DAVBUS_CODEC_STATUS)));

	screamer_write_locked(d, SCREAMER_CODEC_ADDR2, 0);
	screamer_write_locked(d, SCREAMER_CODEC_ADDR4, 0);
	screamer_write_locked(d, SCREAMER_CODEC_ADDR5, 0);
	screamer_write_locked(d, SCREAMER_CODEC_ADDR6, 0);

	mtx_unlock(&d->mutex);

	mix_setdevs(m, SOUND_MASK_VOLUME);

	return (0);
}