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
typedef  scalar_t__ u_int32_t ;
struct cs4231_softc {int dummy; } ;
struct cs4231_channel {scalar_t__ speed; scalar_t__ dir; struct cs4231_softc* parent; } ;
typedef  int /*<<< orphan*/  speed_table ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
#define  CLOCK_XTAL1 129 
#define  CLOCK_XTAL2 128 
 int /*<<< orphan*/  CS4231_LOCK (struct cs4231_softc*) ; 
 int /*<<< orphan*/  CS4231_UNLOCK (struct cs4231_softc*) ; 
 int /*<<< orphan*/  CS_CLOCK_DATA_FORMAT ; 
 int /*<<< orphan*/  CS_CLOCK_DATA_FORMAT_MASK ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 scalar_t__ PCMDIR_PLAY ; 
 scalar_t__ abs (scalar_t__) ; 
 int /*<<< orphan*/  cs4231_chan_fs (struct cs4231_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4231_read (struct cs4231_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
cs4231_chan_setspeed(kobj_t obj, void *data, u_int32_t speed)
{
	typedef struct {
		u_int32_t speed;
		u_int8_t bits;
	} speed_struct;

	const static speed_struct speed_table[] = {
		{5510,  (0 << 1) | CLOCK_XTAL2},
		{5510,  (0 << 1) | CLOCK_XTAL2},
		{6620,  (7 << 1) | CLOCK_XTAL2},
		{8000,  (0 << 1) | CLOCK_XTAL1},
		{9600,  (7 << 1) | CLOCK_XTAL1},
		{11025, (1 << 1) | CLOCK_XTAL2},
		{16000, (1 << 1) | CLOCK_XTAL1},
		{18900, (2 << 1) | CLOCK_XTAL2},
		{22050, (3 << 1) | CLOCK_XTAL2},
		{27420, (2 << 1) | CLOCK_XTAL1},
		{32000, (3 << 1) | CLOCK_XTAL1},
		{33075, (6 << 1) | CLOCK_XTAL2},
		{33075, (4 << 1) | CLOCK_XTAL2},
		{44100, (5 << 1) | CLOCK_XTAL2},
		{48000, (6 << 1) | CLOCK_XTAL1},
	};

	struct cs4231_softc *sc;
	struct cs4231_channel *ch;
	int i, n, sel;
	u_int8_t fs;

	ch = data;
	sc = ch->parent;
	CS4231_LOCK(sc);
	if (ch->speed == speed) {
		CS4231_UNLOCK(sc);
		return (speed);
	}
	n = sizeof(speed_table) / sizeof(speed_struct);

	for (i = 1, sel =0; i < n - 1; i++)
		if (abs(speed - speed_table[i].speed) <
		    abs(speed - speed_table[sel].speed))
			sel = i;	
	DPRINTF(("SPEED: %s : %dHz -> %dHz\n", ch->dir == PCMDIR_PLAY ?
	    "playback" : "capture", speed, speed_table[sel].speed));
	speed = speed_table[sel].speed;

	fs = cs4231_read(sc, CS_CLOCK_DATA_FORMAT);
	fs &= ~CS_CLOCK_DATA_FORMAT_MASK;
	fs |= speed_table[sel].bits;
	cs4231_chan_fs(sc, ch->dir, fs);
	ch->speed = speed;
	CS4231_UNLOCK(sc);

	return (speed);
}