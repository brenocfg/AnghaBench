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
struct params {int seq_rx; scalar_t__ state; int /*<<< orphan*/  tap; int /*<<< orphan*/  wep_len; int /*<<< orphan*/  wep_key; int /*<<< orphan*/  ap; int /*<<< orphan*/  tx; int /*<<< orphan*/  mac; } ;
struct ieee80211_frame {char* i_addr2; int* i_fc; char* i_addr1; char* i_addr3; } ;

/* Variables and functions */
 int IEEE80211_FC0_SUBTYPE_DATA ; 
 int IEEE80211_FC0_SUBTYPE_MASK ; 
 int IEEE80211_FC0_SUBTYPE_SHIFT ; 
 int IEEE80211_FC0_TYPE_CTL ; 
 int IEEE80211_FC0_TYPE_DATA ; 
 int IEEE80211_FC0_TYPE_MASK ; 
 int IEEE80211_FC1_DIR_FROMDS ; 
 int IEEE80211_FC1_PROTECTED ; 
 int IEEE80211_FC1_RETRY ; 
 scalar_t__ S_ASSOCIATED ; 
 int /*<<< orphan*/  ack (struct params*,struct ieee80211_frame*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ for_me (struct ieee80211_frame*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac2str (char*,char*) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int send_ack (int /*<<< orphan*/ ,char*) ; 
 void* seqno (struct ieee80211_frame*) ; 
 int wep_decrypt (struct ieee80211_frame*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

void generic_process(struct ieee80211_frame *wh, struct params *p, int len)
{
	int type, stype;
	int dup = 0;

#if 0
	ack(p, wh);
#endif

#if 0
	if (!for_me(wh, p->mac))
		return;
#endif
	/* ignore my own shit */
	if (memcmp(wh->i_addr2, p->mac, 6) == 0) {
		return;
	}

	type = wh->i_fc[0] & IEEE80211_FC0_TYPE_MASK;
	stype = wh->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK;

	if (for_me(wh, p->mac) && type == IEEE80211_FC0_TYPE_DATA) {
		/* sequence number & dups */
		if (p->seq_rx == -1)
			p->seq_rx = seqno(wh);
		else {
			int s = seqno(wh);
			
			if (s > p->seq_rx) {
				/* normal case */
				if (p->seq_rx + 1 == s) {
#if 0				
					printf("S=%d\n", s);
#endif					
					p->seq_rx = s;
				}	
				else { /* future */
#if 0				
					printf("Got seq %d, prev %d\n",
					       s, p->seq_rx);
#endif					       
					p->seq_rx = s;
				}
			} else { /* we got pas stuff... */
				if (p->seq_rx - s > 1000) {
#if 0				
					printf("Seqno wrap seq %d, last %d\n",
					       s, p->seq_rx);
#endif					       
					/* seqno wrapping ? */
					p->seq_rx = 0;
				}
				else { /* dup */
					dup = 1;
#if 0
					printf("Got dup seq %d, last %d\n",
					       s, p->seq_rx);
#endif					       
				}
			}
		}
	}
#if 0
	if (wh->i_fc[1] & IEEE80211_FC1_RETRY) {
		printf("Got retry\n");
	}
#endif	
#if 0
	if ((wh->i_fc[0] & IEEE80211_FC0_TYPE_MASK) != IEEE80211_FC0_TYPE_CTL) {
		int rc = send_ack(p->tx, wh->i_addr2);
		if (rc == -1)
			err(1, "send_ack()");
		if (rc != 10) {
			printf("Wrote ACK %d/%d\n", rc, 10);
			exit(1);
		}
	}
#endif

	/* data frames */
	if (type == IEEE80211_FC0_TYPE_DATA && !dup) {
		char *ptr;
		char src[6], dst[6];
		int rc;

		if (wh->i_fc[1] & IEEE80211_FC1_DIR_FROMDS) {
			if (memcmp(wh->i_addr2, p->ap, 6) != 0)
				return;
		} else {
			if (memcmp(wh->i_addr1, p->ap, 6) != 0)
				return;
		}
		

		if (p->state < S_ASSOCIATED) {
			printf("Got data when not associated!\n");
			return;
		}
		if (stype != IEEE80211_FC0_SUBTYPE_DATA) {
			printf("Got weird data frame stype=%d\n",
			       stype >> IEEE80211_FC0_SUBTYPE_SHIFT);
			return;
		}

		if (wh->i_fc[1] & IEEE80211_FC1_DIR_FROMDS) {
			memcpy(src, wh->i_addr3, 6);
			memcpy(dst, wh->i_addr1, 6);
		} else {
			memcpy(src, wh->i_addr2, 6);
			memcpy(dst, wh->i_addr3, 6);
		}
		
		ptr = (char*) (wh + 1);

		if (wh->i_fc[1] & IEEE80211_FC1_PROTECTED) {
			if (!p->wep_len) {
				char srca[3*6];
				char dsta[3*6];

				mac2str(srca, src);
				mac2str(dsta, dst);
				printf("Got wep but i aint wep %s->%s %d\n",
				       srca, dsta, len-sizeof(*wh)-8);
				return;
			}
			
			if (wep_decrypt(wh, len, p->wep_key, p->wep_len) == -1){
				char srca[3*6];
				char dsta[3*6];

				mac2str(srca, src);
				mac2str(dsta, dst);
				printf("Can't decrypt %s->%s %d\n", srca, dsta,
				       len-sizeof(*wh)-8);
				return;
			}

			ptr += 4;
			len -= 8;
		}

		/* ether header */
		ptr += 8 - 2;
		ptr -= 6;
		memcpy(ptr, src, 6);
		ptr -= 6;
		memcpy(ptr, dst, 6);

		len -= sizeof(*wh);
		len -= 8;
		len += 14;

		/* send to tap */
		rc = write(p->tap, ptr, len);
		if (rc == -1)
			err(1, "write()");
		if (rc != len) {
			printf("Wrote %d/%d\n", rc, len);
			exit(1);
		}
	}
}