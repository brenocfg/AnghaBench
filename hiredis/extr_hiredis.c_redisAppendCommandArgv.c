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
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  redisContext ;

/* Variables and functions */
 int REDIS_ERR ; 
 int /*<<< orphan*/  REDIS_ERR_OOM ; 
 scalar_t__ REDIS_OK ; 
 scalar_t__ __redisAppendCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __redisSetError (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int redisFormatSdsCommandArgv (int /*<<< orphan*/ *,int,char const**,size_t const*) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 

int redisAppendCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen) {
    sds cmd;
    int len;

    len = redisFormatSdsCommandArgv(&cmd,argc,argv,argvlen);
    if (len == -1) {
        __redisSetError(c,REDIS_ERR_OOM,"Out of memory");
        return REDIS_ERR;
    }

    if (__redisAppendCommand(c,cmd,len) != REDIS_OK) {
        sdsfree(cmd);
        return REDIS_ERR;
    }

    sdsfree(cmd);
    return REDIS_OK;
}