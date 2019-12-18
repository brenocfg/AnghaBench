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
struct malloc_type {int dummy; } ;
struct fw_xferlist {int dummy; } ;
struct fw_xfer {void (* hand ) (struct fw_xfer*) ;void* sc; struct firewire_comm* fc; } ;
struct firewire_comm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (struct fw_xferlist*,struct fw_xfer*,int /*<<< orphan*/ ) ; 
 struct fw_xfer* fw_xfer_alloc_buf (struct malloc_type*,int,int) ; 
 int /*<<< orphan*/  link ; 
 int splfw () ; 
 int /*<<< orphan*/  splx (int) ; 

int
fw_xferlist_add(struct fw_xferlist *q, struct malloc_type *type,
    int slen, int rlen, int n,
    struct firewire_comm *fc, void *sc, void (*hand)(struct fw_xfer *))
{
	int i, s;
	struct fw_xfer *xfer;

	for (i = 0; i < n; i++) {
		xfer = fw_xfer_alloc_buf(type, slen, rlen);
		if (xfer == NULL)
			return (i);
		xfer->fc = fc;
		xfer->sc = sc;
		xfer->hand = hand;
		s = splfw();
		STAILQ_INSERT_TAIL(q, xfer, link);
		splx(s);
	}
	return (n);
}