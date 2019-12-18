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
 int BURGUNDY_ISA_SF0 ; 
 int BURGUNDY_ISSAL_REG ; 
 int BURGUNDY_ISSAR_REG ; 
 int BURGUNDY_ISS_UNITY ; 
 int BURGUNDY_MIX0_REG ; 
 int BURGUNDY_MIX1_REG ; 
 int BURGUNDY_MIX2_REG ; 
 int BURGUNDY_MIX3_REG ; 
 int BURGUNDY_MIX_ISA ; 
 int BURGUNDY_MXS2L_REG ; 
 int BURGUNDY_MXS2R_REG ; 
 int BURGUNDY_MXS_UNITY ; 
 int BURGUNDY_OS0_MIX2 ; 
 int BURGUNDY_OS1_MIX2 ; 
 int BURGUNDY_OSS0L_REG ; 
 int BURGUNDY_OSS0R_REG ; 
 int BURGUNDY_OSS1L_REG ; 
 int BURGUNDY_OSS1R_REG ; 
 int BURGUNDY_OSS_UNITY ; 
 int BURGUNDY_OS_REG ; 
 int BURGUNDY_SDIN_REG ; 
 int /*<<< orphan*/  DAVBUS_CODEC_STATUS ; 
 int /*<<< orphan*/  SOUND_MASK_VOLUME ; 
 int /*<<< orphan*/  burgundy_read_status (struct davbus_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  burgundy_set_outputs (struct davbus_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  burgundy_write_locked (struct davbus_softc*,int,int) ; 
 int /*<<< orphan*/  bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct davbus_softc* mix_getdevinfo (struct snd_mixer*) ; 
 int /*<<< orphan*/  mix_setdevs (struct snd_mixer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
burgundy_init(struct snd_mixer *m)
{
	struct davbus_softc *d;

	d = mix_getdevinfo(m);

	d->read_status = burgundy_read_status;
	d->set_outputs = burgundy_set_outputs;

	/*
	 * We configure the Burgundy codec as follows:
	 *
	 * 	o Input subframe 0 is connected to input digital
	 *	  stream A (ISA).
	 *	o Stream A (ISA) is mixed in mixer 2 (MIX2).
	 *	o Output of mixer 2 (MIX2) is routed to output sources
	 *	  OS0 and OS1 which can be converted to analog.
	 *
	 */
	mtx_lock(&d->mutex);

	burgundy_write_locked(d, 0x16700, 0x40);
	
	burgundy_write_locked(d, BURGUNDY_MIX0_REG, 0); 
	burgundy_write_locked(d, BURGUNDY_MIX1_REG, 0);
	burgundy_write_locked(d, BURGUNDY_MIX2_REG, BURGUNDY_MIX_ISA);
	burgundy_write_locked(d, BURGUNDY_MIX3_REG, 0);

	burgundy_write_locked(d, BURGUNDY_OS_REG, BURGUNDY_OS0_MIX2 | 
	    BURGUNDY_OS1_MIX2);

	burgundy_write_locked(d, BURGUNDY_SDIN_REG, BURGUNDY_ISA_SF0);

	/* Set several digital scalers to unity gain. */
	burgundy_write_locked(d, BURGUNDY_MXS2L_REG, BURGUNDY_MXS_UNITY);
	burgundy_write_locked(d, BURGUNDY_MXS2R_REG, BURGUNDY_MXS_UNITY);
	burgundy_write_locked(d, BURGUNDY_OSS0L_REG, BURGUNDY_OSS_UNITY);
	burgundy_write_locked(d, BURGUNDY_OSS0R_REG, BURGUNDY_OSS_UNITY);
	burgundy_write_locked(d, BURGUNDY_OSS1L_REG, BURGUNDY_OSS_UNITY);
	burgundy_write_locked(d, BURGUNDY_OSS1R_REG, BURGUNDY_OSS_UNITY);
	burgundy_write_locked(d, BURGUNDY_ISSAL_REG, BURGUNDY_ISS_UNITY);
	burgundy_write_locked(d, BURGUNDY_ISSAR_REG, BURGUNDY_ISS_UNITY);

	burgundy_set_outputs(d, burgundy_read_status(d, 
	    bus_read_4(d->reg, DAVBUS_CODEC_STATUS)));

	mtx_unlock(&d->mutex);

	mix_setdevs(m, SOUND_MASK_VOLUME);

	return (0);
}