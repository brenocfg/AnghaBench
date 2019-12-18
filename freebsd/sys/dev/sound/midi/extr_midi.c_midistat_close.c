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
 int EBADF ; 
 int /*<<< orphan*/  MIDI_DEBUG (int,int /*<<< orphan*/ ) ; 
 scalar_t__ midistat_isopen ; 
 int /*<<< orphan*/  midistat_lock ; 
 int /*<<< orphan*/  midistat_sbuf ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sbuf_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
midistat_close(struct cdev *i_dev, int flags, int mode, struct thread *td)
{
	MIDI_DEBUG(1, printf("midistat_close\n"));
	sx_xlock(&midistat_lock);
	if (!midistat_isopen) {
		sx_xunlock(&midistat_lock);
		return EBADF;
	}
	sbuf_delete(&midistat_sbuf);
	midistat_isopen = 0;
	sx_xunlock(&midistat_lock);
	return 0;
}