#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct connstate {scalar_t__ getmonitors; scalar_t__ getoutputinfo; TYPE_1__* clientw; } ;
struct TYPE_6__ {scalar_t__ sequence; } ;
typedef  TYPE_2__ generic_x11_reply_t ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * buf; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * buf; } ;
struct TYPE_5__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 TYPE_4__ getmonitors_reply ; 
 TYPE_3__ getoutputinfo_reply ; 
 int /*<<< orphan*/  must_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  writeall (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool handle_sequence(struct connstate *connstate, uint16_t sequence) {
    /* BEGIN RandR 1.5 specific */
    if (sequence == connstate->getmonitors) {
        printf("RRGetMonitors reply!\n");
        if (getmonitors_reply.buf != NULL) {
            printf("injecting reply\n");
            ((generic_x11_reply_t *)getmonitors_reply.buf)->sequence = sequence;
            must_write(writeall(connstate->clientw->fd, getmonitors_reply.buf, getmonitors_reply.len));
            return true;
        }
    }

    if (sequence == connstate->getoutputinfo) {
        printf("RRGetOutputInfo reply!\n");
        if (getoutputinfo_reply.buf != NULL) {
            printf("injecting reply\n");
            ((generic_x11_reply_t *)getoutputinfo_reply.buf)->sequence = sequence;
            must_write(writeall(connstate->clientw->fd, getoutputinfo_reply.buf, getoutputinfo_reply.len));
            return true;
        }
    }
    /* END RandR 1.5 specific */

    return false;
}