#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * sds ;
typedef  int /*<<< orphan*/  h2o_redis_command_t ;
typedef  int /*<<< orphan*/  h2o_redis_command_cb ;
typedef  int /*<<< orphan*/  h2o_redis_client_t ;

/* Variables and functions */
 int /*<<< orphan*/ * create_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  detect_command_type (int /*<<< orphan*/ *) ; 
 int redisFormatSdsCommandArgv (int /*<<< orphan*/ **,int,char const**,size_t const*) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_command (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

h2o_redis_command_t *h2o_redis_command_argv(h2o_redis_client_t *client, h2o_redis_command_cb cb, void *cb_data, int argc,
                                            const char **argv, const size_t *argvlen)
{
    sds sdscmd;
    int len;
    len = redisFormatSdsCommandArgv(&sdscmd, argc, argv, argvlen);
    if (len < 0) {
        sdscmd = NULL;
        len = 0;
    }

    h2o_redis_command_t *command = create_command(client, cb, cb_data, detect_command_type(sdscmd));
    send_command(client, command, sdscmd, len);
    sdsfree(sdscmd);
    return command;
}