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
typedef  int /*<<< orphan*/  yrmcds_error ;
struct TYPE_3__ {int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ yrmcds_cnt ;
typedef  int /*<<< orphan*/  tv ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVTIMEO ; 
 int /*<<< orphan*/  SO_SNDTIMEO ; 
 int /*<<< orphan*/  YRMCDS_BAD_ARGUMENT ; 
 int /*<<< orphan*/  YRMCDS_OK ; 
 int /*<<< orphan*/  YRMCDS_SYSTEM_ERROR ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*,int) ; 

yrmcds_error
yrmcds_cnt_set_timeout(yrmcds_cnt* c, int timeout) {
    if( c == NULL || timeout < 0 )
        return YRMCDS_BAD_ARGUMENT;

    struct timeval tv;
    tv.tv_sec = timeout;
    tv.tv_usec = 0;

    if( setsockopt(c->sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) == -1 )
        return YRMCDS_SYSTEM_ERROR;
    if( setsockopt(c->sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) == -1 )
        return YRMCDS_SYSTEM_ERROR;
    return YRMCDS_OK;
}