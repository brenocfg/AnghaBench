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
struct params {int /*<<< orphan*/  tap; int /*<<< orphan*/  wep_len; int /*<<< orphan*/  wep_key; int /*<<< orphan*/  mac; } ;
struct ieee80211_frame {char* i_addr1; char* i_addr3; int* i_fc; char* i_addr2; } ;

/* Variables and functions */
 int IEEE80211_FC1_PROTECTED ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  relay_data (struct params*,struct ieee80211_frame*,int) ; 
 int wep_decrypt (struct ieee80211_frame*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

void read_real_data(struct params *p, struct ieee80211_frame *wh, int len)
{
	char dst[6];
	int rc;
	char *ptr = (char*) (wh+1);

	/* stuff not for this net */
	if (memcmp(wh->i_addr1, p->mac, 6) != 0)
		return;

	/* relay data */
	if (memcmp(wh->i_addr3, p->mac, 6) != 0)
		relay_data(p, wh, len);

	memcpy(dst, wh->i_addr3, 6);


	if (wh->i_fc[1] & IEEE80211_FC1_PROTECTED) {
		if (!p->wep_len) {
			printf("Got wep but i aint wep\n");
			return;
		}
		
		if (wep_decrypt(wh, len, p->wep_key, p->wep_len) == -1){
			printf("Can't decrypt\n");
			return;
		}

		ptr += 4;
		len -= 8;
	}

	/* ether header */
	ptr += 8 - 2;
	ptr -= 6;
	memcpy(ptr, wh->i_addr2, 6);
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