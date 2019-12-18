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
typedef  long uLong ;
struct timeval {int tv_sec; int tv_usec; } ;
struct params {char* ap; char* mac; int data_len; int prga_len; char* data; char* prga; void* state; int /*<<< orphan*/  iv; scalar_t__ rx; int /*<<< orphan*/  last; } ;
struct ieee80211_frame {int /*<<< orphan*/  i_addr1; int /*<<< orphan*/  i_addr3; int /*<<< orphan*/  i_addr2; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_DATA ; 
 int /*<<< orphan*/  IEEE80211_FC0_TYPE_DATA ; 
 void* S_START ; 
 char* Z_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 long crc32 (long,char*,int) ; 
 int elapsed (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  frame_type (struct ieee80211_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_frame* get_wifi (char*,int*) ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  save_prga (struct params*) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int sniff (scalar_t__,char*,int) ; 

void wait_relay(struct params *p)
{
	int tout = 20*1000;
	struct timeval now;
	int el;
	fd_set fds;
	int rc;
	char buf[4096];
	struct ieee80211_frame *wh;
	char *ptr;
	uLong crc = crc32(0L, Z_NULL, 0);
	uLong *pcrc;

	if (gettimeofday(&now, NULL) == -1)
		err(1, "gettimeofday()");

	el = elapsed(&p->last, &now);
	if (el >= tout) {
#if 0	
		printf("No relay\n");
#endif		
		p->state = S_START;
		return;
	}
	el = tout - el;
	now.tv_sec = el/1000/1000;
	now.tv_usec = el - now.tv_sec*1000*1000;

	FD_ZERO(&fds);
	FD_SET(p->rx, &fds);
	if (select(p->rx+1, &fds, NULL, NULL, &now) == -1)
		err(1, "select()");
	
	if (!FD_ISSET(p->rx, &fds))
		return;

	/* get relay */
        rc = sniff(p->rx, buf, sizeof(buf));
        if (rc == -1)
                err(1, "sniff()");

        wh = get_wifi(buf, &rc);
        if (!wh)
                return;

	if (!frame_type(wh, IEEE80211_FC0_TYPE_DATA,
			IEEE80211_FC0_SUBTYPE_DATA))
		return;

	if (memcmp(wh->i_addr2, p->ap, 6) != 0)
		return;

	if (memcmp(wh->i_addr3, p->mac, 6) != 0)
		return;

	if (memcmp(wh->i_addr1, "\xff\xff\xff\xff\xff\xff", 6) != 0)
		return;

	/* lends different due to padding? */
	if ( (rc - sizeof(*wh) - 8) != p->data_len)
		return;
	
	/* grab new PRGA */
	assert(p->data_len >= p->prga_len);
	ptr = (char*) (wh+1);
	memcpy(p->iv, ptr, 3);
	ptr += 4;

	crc = crc32(crc, p->data, p->data_len);
	pcrc = (uLong*) &p->data[p->data_len]; /* XXX overflow ph33r */
	*pcrc = crc;

	for (rc = 0; rc < p->data_len+4; rc++)
		p->prga[rc] = p->data[rc] ^ ptr[rc];

	p->prga_len = p->data_len+4;
	p->state = S_START;
	save_prga(p);
}