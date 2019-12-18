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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 unsigned char* get_80211 (unsigned char**,int*,int*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int read (int,unsigned char*,int) ; 

__attribute__((used)) static int read_packet(int fd, unsigned char *dst, int len)
{
	static unsigned char buf[4096];
	static int totlen = 0;
	static unsigned char *next = buf;
        unsigned char *pkt;
        int plen;
        
        assert(len > 0);

        /* need to read more */
        if (totlen == 0) {
                totlen = read(fd, buf, sizeof(buf));
                if (totlen == -1) {
                        totlen = 0;
                        return -1;
                }
                next = buf;
        }
        
        /* read 802.11 packet */
        pkt = get_80211(&next, &totlen, &plen);
        if (plen > len)
                plen = len;
        assert(plen > 0);
        memcpy(dst, pkt, plen);

        return plen;
}