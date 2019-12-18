#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char* staticbuf; size_t maxsize; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ WPACKET ;

/* Variables and functions */
 size_t maxmaxsize (size_t) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int wpacket_intern_init_len (TYPE_1__*,size_t) ; 

int WPACKET_init_static_len(WPACKET *pkt, unsigned char *buf, size_t len,
                            size_t lenbytes)
{
    size_t max = maxmaxsize(lenbytes);

    /* Internal API, so should not fail */
    if (!ossl_assert(buf != NULL && len > 0))
        return 0;

    pkt->staticbuf = buf;
    pkt->buf = NULL;
    pkt->maxsize = (max < len) ? max : len;

    return wpacket_intern_init_len(pkt, lenbytes);
}