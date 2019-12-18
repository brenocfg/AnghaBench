#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
struct fifolog_writer {int lastsync; scalar_t__ ibufptr; TYPE_1__* ff; scalar_t__ obufsize; scalar_t__ obuf; int /*<<< orphan*/  flag; int /*<<< orphan*/  ibuf; int /*<<< orphan*/ * cnt; scalar_t__ writerate; scalar_t__ lastwrite; scalar_t__ cleanup; scalar_t__ syncrate; } ;
struct TYPE_5__ {scalar_t__ avail_in; scalar_t__ avail_out; scalar_t__ next_out; int /*<<< orphan*/  next_in; } ;
struct TYPE_4__ {TYPE_2__* zs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIFOLOG_FLG_SYNC ; 
 size_t FIFOLOG_PT_FLUSH ; 
 size_t FIFOLOG_PT_SYNC ; 
 int Z_BUF_ERROR ; 
 int Z_FINISH ; 
 int Z_NO_FLUSH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int Z_SYNC_FLUSH ; 
 int /*<<< orphan*/  assert (int) ; 
 int deflate (TYPE_2__*,int) ; 
 int deflateReset (TYPE_2__*) ; 
 int fifolog_write_output (struct fifolog_writer*,int,int) ; 

__attribute__((used)) static int
fifolog_write_gzip(struct fifolog_writer *f, time_t now)
{
	int i, fl, retval = 0;

	assert(now != 0);
	if (f->cleanup || now >= (int)(f->lastsync + f->syncrate)) {
		f->cleanup = 0;
		fl = Z_FINISH;
		f->cnt[FIFOLOG_PT_SYNC]++;
	} else if (now >= (int)(f->lastwrite + f->writerate)) {
		fl = Z_SYNC_FLUSH;
		f->cnt[FIFOLOG_PT_FLUSH]++;
	} else if (f->ibufptr == 0)
		return (0);
	else
		fl = Z_NO_FLUSH;

	f->ff->zs->avail_in = f->ibufptr;
	f->ff->zs->next_in = f->ibuf;

	while (1) {
		i = deflate(f->ff->zs, fl);
		assert(i == Z_OK || i == Z_BUF_ERROR || i == Z_STREAM_END);

		i = fifolog_write_output(f, fl, now);
		if (i == 0)
			break;
		if (i < 0)
			retval = -1;
	}
	assert(f->ff->zs->avail_in == 0);
	f->ibufptr = 0;
	if (fl == Z_FINISH) {
		f->flag |= FIFOLOG_FLG_SYNC;
		f->ff->zs->next_out = f->obuf + 9;
		f->ff->zs->avail_out = f->obufsize - 9;
		f->lastsync = now;
		assert(Z_OK == deflateReset(f->ff->zs));
	}
	return (retval);
}