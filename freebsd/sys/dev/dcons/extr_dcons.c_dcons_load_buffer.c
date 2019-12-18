#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size; char* buf; int gen; int pos; int /*<<< orphan*/ * ptr; } ;
struct TYPE_3__ {int size; char* buf; int gen; int pos; int /*<<< orphan*/ * ptr; } ;
struct dcons_softc {TYPE_2__ i; TYPE_1__ o; int /*<<< orphan*/  brk_state; } ;
struct dcons_buf {scalar_t__ version; int magic; int /*<<< orphan*/ * iptr; int /*<<< orphan*/ * optr; int /*<<< orphan*/ * ioffset; int /*<<< orphan*/ * ooffset; int /*<<< orphan*/ * isize; int /*<<< orphan*/ * osize; } ;

/* Variables and functions */
 int DCONS_GEN_SHIFT ; 
 int DCONS_HEADER_SIZE ; 
 int /*<<< orphan*/  DCONS_MAGIC ; 
 int DCONS_NPORT ; 
 int DCONS_POS_MASK ; 
 int /*<<< orphan*/  DCONS_VERSION ; 
 int /*<<< orphan*/  STATE0 ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

int
dcons_load_buffer(struct dcons_buf *buf, int size, struct dcons_softc *sc)
{
	int port, s;
	struct dcons_softc *dc;

	if (buf->version != htonl(DCONS_VERSION))
		return (-1);

	s = DCONS_HEADER_SIZE;
	for (port = 0; port < DCONS_NPORT; port ++) {
		dc = &sc[port];
		dc->o.size = ntohl(buf->osize[port]);
		dc->i.size = ntohl(buf->isize[port]);
		dc->o.buf = (char *)buf + ntohl(buf->ooffset[port]);
		dc->i.buf = (char *)buf + ntohl(buf->ioffset[port]);
		dc->o.gen = ntohl(buf->optr[port]) >> DCONS_GEN_SHIFT;
		dc->i.gen = ntohl(buf->iptr[port]) >> DCONS_GEN_SHIFT;
		dc->o.pos = ntohl(buf->optr[port]) & DCONS_POS_MASK;
		dc->i.pos = ntohl(buf->iptr[port]) & DCONS_POS_MASK;
		dc->o.ptr = &buf->optr[port];
		dc->i.ptr = &buf->iptr[port];
		dc->brk_state = STATE0;

		s += dc->o.size + dc->i.size;
	}

	/* sanity check */
	if (s > size)
		return (-1);

	buf->magic = ntohl(DCONS_MAGIC);

	return (0);
}