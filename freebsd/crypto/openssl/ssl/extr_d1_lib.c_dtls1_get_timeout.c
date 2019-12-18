#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_7__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_6__ {TYPE_1__* d1; } ;
struct TYPE_5__ {TYPE_3__ next_timeout; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  get_current_time (struct timeval*) ; 
 int /*<<< orphan*/  memcpy (struct timeval*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (struct timeval*,int /*<<< orphan*/ ,int) ; 

struct timeval *dtls1_get_timeout(SSL *s, struct timeval *timeleft)
{
    struct timeval timenow;

    /* If no timeout is set, just return NULL */
    if (s->d1->next_timeout.tv_sec == 0 && s->d1->next_timeout.tv_usec == 0) {
        return NULL;
    }

    /* Get current time */
    get_current_time(&timenow);

    /* If timer already expired, set remaining time to 0 */
    if (s->d1->next_timeout.tv_sec < timenow.tv_sec ||
        (s->d1->next_timeout.tv_sec == timenow.tv_sec &&
         s->d1->next_timeout.tv_usec <= timenow.tv_usec)) {
        memset(timeleft, 0, sizeof(*timeleft));
        return timeleft;
    }

    /* Calculate time left until timer expires */
    memcpy(timeleft, &(s->d1->next_timeout), sizeof(struct timeval));
    timeleft->tv_sec -= timenow.tv_sec;
    timeleft->tv_usec -= timenow.tv_usec;
    if (timeleft->tv_usec < 0) {
        timeleft->tv_sec--;
        timeleft->tv_usec += 1000000;
    }

    /*
     * If remaining time is less than 15 ms, set it to 0 to prevent issues
     * because of small divergences with socket timeouts.
     */
    if (timeleft->tv_sec == 0 && timeleft->tv_usec < 15000) {
        memset(timeleft, 0, sizeof(*timeleft));
    }

    return timeleft;
}