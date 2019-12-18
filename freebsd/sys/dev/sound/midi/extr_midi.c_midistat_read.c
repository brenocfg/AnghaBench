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
struct uio {scalar_t__ uio_offset; int /*<<< orphan*/  uio_resid; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int /*<<< orphan*/  MIDI_DEBUG (int,int /*<<< orphan*/ ) ; 
 long lmin (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  midistat_isopen ; 
 int /*<<< orphan*/  midistat_lock ; 
 int /*<<< orphan*/  midistat_sbuf ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ sbuf_data (int /*<<< orphan*/ *) ; 
 scalar_t__ sbuf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int uiomove (scalar_t__,long,struct uio*) ; 

__attribute__((used)) static int
midistat_read(struct cdev *i_dev, struct uio *uio, int flag)
{
	long l;
	int err;

	MIDI_DEBUG(4, printf("midistat_read\n"));
	sx_xlock(&midistat_lock);
	if (!midistat_isopen) {
		sx_xunlock(&midistat_lock);
		return EBADF;
	}
	if (uio->uio_offset < 0 || uio->uio_offset > sbuf_len(&midistat_sbuf)) {
		sx_xunlock(&midistat_lock);
		return EINVAL;
	}
	err = 0;
	l = lmin(uio->uio_resid, sbuf_len(&midistat_sbuf) - uio->uio_offset);
	if (l > 0) {
		err = uiomove(sbuf_data(&midistat_sbuf) + uio->uio_offset, l,
		    uio);
	}
	sx_xunlock(&midistat_lock);
	return err;
}