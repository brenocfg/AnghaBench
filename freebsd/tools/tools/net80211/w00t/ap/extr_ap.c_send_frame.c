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
struct params {int /*<<< orphan*/  seq; int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int inject (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

void send_frame(struct params *p, void *buf, int len)
{       
        int rc;
        
        rc = inject(p->tx, buf, len);
        if (rc == -1)
                err(1, "inject()");
        if (rc != len) {
                printf("injected %d/%d\n", rc, len);
                exit(1);
        }
        p->seq++;
}