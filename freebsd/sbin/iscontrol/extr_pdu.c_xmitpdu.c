#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdu_t ;
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ isess_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSISEND ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pukeText (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ vflag ; 

int
xmitpdu(isess_t *sess, pdu_t *pp)
{
     if(ioctl(sess->fd, ISCSISEND, pp)) {
	  perror("xmitpdu");
	  return -1;
     }
     if(vflag)
	  pukeText("I-", pp);

     return 0;
}