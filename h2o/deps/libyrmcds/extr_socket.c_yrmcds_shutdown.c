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
typedef  TYPE_1__ yrmcds ;

/* Variables and functions */
 int /*<<< orphan*/  SHUT_RD ; 
 int /*<<< orphan*/  YRMCDS_BAD_ARGUMENT ; 
 int /*<<< orphan*/  YRMCDS_OK ; 
 int /*<<< orphan*/  YRMCDS_SYSTEM_ERROR ; 
 int shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

yrmcds_error yrmcds_shutdown(yrmcds* c) {
    if( c == NULL )
        return YRMCDS_BAD_ARGUMENT;
    if( shutdown(c->sock, SHUT_RD) == -1 ) {
        return YRMCDS_SYSTEM_ERROR;
    }
    return YRMCDS_OK;
}