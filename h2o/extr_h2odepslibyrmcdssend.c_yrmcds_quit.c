#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yrmcds_error ;
struct TYPE_5__ {scalar_t__ text_mode; } ;
typedef  TYPE_1__ yrmcds ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  YRMCDS_BAD_ARGUMENT ; 
 int /*<<< orphan*/  YRMCDS_CMD_QUIT ; 
 int /*<<< orphan*/  YRMCDS_CMD_QUITQ ; 
 int /*<<< orphan*/  send_command (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yrmcds_text_quit (TYPE_1__*,int /*<<< orphan*/ *) ; 

yrmcds_error yrmcds_quit(yrmcds* c, int quiet, uint32_t* serial) {
    if( c == NULL )
        return YRMCDS_BAD_ARGUMENT;

    if( c->text_mode )
        return yrmcds_text_quit(c, serial);

    return send_command(c, quiet ? YRMCDS_CMD_QUITQ : YRMCDS_CMD_QUIT,
                        0, serial, 0, NULL, 0, NULL, 0, NULL);
}