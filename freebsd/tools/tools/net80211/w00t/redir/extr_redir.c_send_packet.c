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
struct params {int packet_len; int /*<<< orphan*/  last; scalar_t__ packet; int /*<<< orphan*/  data_try; int /*<<< orphan*/  tx; } ;
struct ieee80211_frame {int /*<<< orphan*/ * i_fc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FC1_RETRY ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int inject (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

void send_packet(struct params *p)
{       
        int rc;
        struct ieee80211_frame *wh;

        rc = inject(p->tx, p->packet, p->packet_len);
        if (rc == -1)
                err(1, "inject()");
        if (rc != p->packet_len) {
                printf("Wrote %d/%d\n", rc, p->packet_len);
                exit(1);
        }
        
        p->data_try++;
        wh = (struct ieee80211_frame*) p->packet;
        wh->i_fc[1] |= IEEE80211_FC1_RETRY;

        if (gettimeofday(&p->last, NULL) == -1)
                err(1, "gettimeofday()");
}