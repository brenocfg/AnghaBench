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
struct params {int packet_len; int /*<<< orphan*/  last; int /*<<< orphan*/  packet; int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int inject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

void send_packet(struct params *p)
{       
        int rc;

        rc = inject(p->tx, p->packet, p->packet_len);
        if (rc == -1)
                err(1, "inject()");
        if (rc != p->packet_len) {
                printf("Wrote %d/%d\n", rc, p->packet_len);
                exit(1);
        }
        
        if (gettimeofday(&p->last, NULL) == -1)
                err(1, "gettimeofday()");
}