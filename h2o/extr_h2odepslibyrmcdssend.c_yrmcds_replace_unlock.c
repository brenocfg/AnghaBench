#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yrmcds_error ;
struct TYPE_4__ {scalar_t__ text_mode; } ;
typedef  TYPE_1__ yrmcds ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  YRMCDS_CMD_RAU ; 
 int /*<<< orphan*/  YRMCDS_CMD_RAUQ ; 
 int /*<<< orphan*/  YRMCDS_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  send_data (TYPE_1__*,int /*<<< orphan*/ ,char const*,size_t,char const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

yrmcds_error yrmcds_replace_unlock(yrmcds* c, const char* key, size_t key_len,
                                   const char* data, size_t data_len,
                                   uint32_t flags, uint32_t expire,
                                   int quiet, uint32_t* serial) {
    if( c && c->text_mode )
        return YRMCDS_NOT_IMPLEMENTED;

    return send_data(c, quiet ? YRMCDS_CMD_RAUQ : YRMCDS_CMD_RAU,
                     key, key_len, data, data_len, flags, expire, 0, serial);
}