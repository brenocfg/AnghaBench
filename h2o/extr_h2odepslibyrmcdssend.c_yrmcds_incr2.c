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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  extras ;

/* Variables and functions */
 int /*<<< orphan*/  YRMCDS_BAD_ARGUMENT ; 
 int /*<<< orphan*/  YRMCDS_CMD_INCREMENT ; 
 int /*<<< orphan*/  YRMCDS_CMD_INCREMENTQ ; 
 int /*<<< orphan*/  YRMCDS_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  hton32 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hton64 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  send_command (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,char const*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

yrmcds_error yrmcds_incr2(yrmcds* c, const char* key, size_t key_len,
                          uint64_t value, uint64_t initial, uint32_t expire,
                          int quiet, uint32_t* serial) {
    if( c == NULL || key == NULL || key_len == 0 )
        return YRMCDS_BAD_ARGUMENT;

    if( c->text_mode )
        return YRMCDS_NOT_IMPLEMENTED;

    char extras[20];
    hton64(value, extras);
    hton64(initial, &extras[8]);
    hton32(expire, &extras[16]);
    return send_command(c, quiet ? YRMCDS_CMD_INCREMENTQ : YRMCDS_CMD_INCREMENT,
                        0, serial, key_len, key,
                        sizeof(extras), extras, 0, NULL);
}