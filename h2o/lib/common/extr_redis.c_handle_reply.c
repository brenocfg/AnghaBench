#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__** element; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ redisReply ;
struct TYPE_10__ {int type; int /*<<< orphan*/  data; int /*<<< orphan*/  (* cb ) (TYPE_2__*,int /*<<< orphan*/ ,char const*) ;} ;
typedef  TYPE_3__ h2o_redis_command_t ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  str; } ;

/* Variables and functions */
#define  H2O_REDIS_COMMAND_TYPE_PSUBSCRIBE 129 
#define  H2O_REDIS_COMMAND_TYPE_SUBSCRIBE 128 
 int /*<<< orphan*/  REDIS_REPLY_ARRAY ; 
 int /*<<< orphan*/  dispose_command (TYPE_3__*) ; 
 int /*<<< orphan*/  strncasecmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void handle_reply(h2o_redis_command_t *command, redisReply *reply, const char *errstr)
{
    if (command->cb != NULL)
        command->cb(reply, command->data, errstr);

    switch (command->type) {
    case H2O_REDIS_COMMAND_TYPE_SUBSCRIBE:
    case H2O_REDIS_COMMAND_TYPE_PSUBSCRIBE:
        if (reply != NULL && reply->type == REDIS_REPLY_ARRAY) {
            char *unsub = command->type == H2O_REDIS_COMMAND_TYPE_SUBSCRIBE ? "unsubscribe" : "punsubscribe";
            if (strncasecmp(reply->element[0]->str, unsub, reply->element[0]->len) == 0) {
                dispose_command(command);
            } else {
                /* (p)subscribe commands doesn't get freed until (p)unsubscribe or disconnect */
            }
        } else {
            dispose_command(command);
        }
        break;
    default:
        dispose_command(command);
    }
}