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
struct thread {int dummy; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  MIDI_DEBUG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBUF_AUTOEXTEND ; 
 int midistat_isopen ; 
 int /*<<< orphan*/  midistat_lock ; 
 scalar_t__ midistat_prepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  midistat_sbuf ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * sbuf_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
midistat_open(struct cdev *i_dev, int flags, int mode, struct thread *td)
{
	int error;

	MIDI_DEBUG(1, printf("midistat_open\n"));

	sx_xlock(&midistat_lock);
	if (midistat_isopen) {
		sx_xunlock(&midistat_lock);
		return EBUSY;
	}
	midistat_isopen = 1;
	if (sbuf_new(&midistat_sbuf, NULL, 4096, SBUF_AUTOEXTEND) == NULL) {
		error = ENXIO;
		goto out;
	}
	error = (midistat_prepare(&midistat_sbuf) > 0) ? 0 : ENOMEM;
out:
	if (error)
		midistat_isopen = 0;
	sx_xunlock(&midistat_lock);
	return error;
}