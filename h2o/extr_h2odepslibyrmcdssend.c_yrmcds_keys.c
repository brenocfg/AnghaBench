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
 int /*<<< orphan*/  YRMCDS_BAD_ARGUMENT ; 
 int /*<<< orphan*/  YRMCDS_CMD_KEYS ; 
 int /*<<< orphan*/  YRMCDS_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  send_command (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

yrmcds_error yrmcds_keys(yrmcds* c, const char* prefix, size_t prefix_len,
                         uint32_t* serial) {
    if( c == NULL ||
        (prefix == NULL && prefix_len != 0) ||
        (prefix != NULL && prefix_len == 0) )
        return YRMCDS_BAD_ARGUMENT;

    if( c->text_mode )
        return YRMCDS_NOT_IMPLEMENTED;

    return send_command(c, YRMCDS_CMD_KEYS,
                        0, serial, prefix_len, prefix, 0, NULL, 0, NULL);
}