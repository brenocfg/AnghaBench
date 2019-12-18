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
struct TYPE_3__ {int wantRead; int pendingWrite; } ;
typedef  TYPE_1__ redisSSLContext ;

/* Variables and functions */
 int SSL_ERROR_WANT_READ ; 
 int SSL_ERROR_WANT_WRITE ; 

__attribute__((used)) static int maybeCheckWant(redisSSLContext *rssl, int rv) {
    /**
     * If the error is WANT_READ or WANT_WRITE, the appropriate flags are set
     * and true is returned. False is returned otherwise
     */
    if (rv == SSL_ERROR_WANT_READ) {
        rssl->wantRead = 1;
        return 1;
    } else if (rv == SSL_ERROR_WANT_WRITE) {
        rssl->pendingWrite = 1;
        return 1;
    } else {
        return 0;
    }
}