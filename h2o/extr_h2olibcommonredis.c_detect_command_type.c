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
typedef  int /*<<< orphan*/  h2o_redis_command_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_REDIS_COMMAND_TYPE_ERROR ; 
 int /*<<< orphan*/  H2O_REDIS_COMMAND_TYPE_MONITOR ; 
 int /*<<< orphan*/  H2O_REDIS_COMMAND_TYPE_NORMAL ; 
 int /*<<< orphan*/  H2O_REDIS_COMMAND_TYPE_PSUBSCRIBE ; 
 int /*<<< orphan*/  H2O_REDIS_COMMAND_TYPE_PUNSUBSCRIBE ; 
 int /*<<< orphan*/  H2O_REDIS_COMMAND_TYPE_SUBSCRIBE ; 
 int /*<<< orphan*/  H2O_REDIS_COMMAND_TYPE_UNSUBSCRIBE ; 
 int /*<<< orphan*/  assert (int) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

__attribute__((used)) static h2o_redis_command_type_t detect_command_type(const char *formatted)
{
#define CHECK(c)                                                                                                                   \
    if (c == NULL)                                                                                                                 \
    return H2O_REDIS_COMMAND_TYPE_ERROR

    char *p = (char *)formatted;
    CHECK(p);

    assert(p[0] == '*');

    p = strchr(p, '$');
    CHECK(p);
    p = strchr(p, '\n');
    CHECK(p);
    ++p;
    CHECK(p);

#define MATCH(c, target) strncasecmp(c, target, sizeof(target) - 1) == 0
    if (MATCH(p, "subscribe\r\n"))
        return H2O_REDIS_COMMAND_TYPE_SUBSCRIBE;
    if (MATCH(p, "unsubscribe\r\n"))
        return H2O_REDIS_COMMAND_TYPE_UNSUBSCRIBE;
    if (MATCH(p, "psubscribe\r\n"))
        return H2O_REDIS_COMMAND_TYPE_PSUBSCRIBE;
    if (MATCH(p, "punsubscribe\r\n"))
        return H2O_REDIS_COMMAND_TYPE_PUNSUBSCRIBE;
    if (MATCH(p, "monitor\r\n"))
        return H2O_REDIS_COMMAND_TYPE_MONITOR;
#undef MATCH
    return H2O_REDIS_COMMAND_TYPE_NORMAL;
#undef CHECK
}