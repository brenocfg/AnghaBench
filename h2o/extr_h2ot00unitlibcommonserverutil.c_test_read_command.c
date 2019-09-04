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
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  bytes; } ;
typedef  TYPE_1__ h2o_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int WEXITSTATUS (int) ; 
 int WIFEXITED (int) ; 
 int /*<<< orphan*/  h2o_buffer_dispose (TYPE_1__**) ; 
 int h2o_memis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int h2o_read_command (char*,char**,TYPE_1__**,int*) ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

__attribute__((used)) static void test_read_command(void)
{
    char *argv[] = {"t/00unit/assets/read_command.pl", "hello", NULL};
    h2o_buffer_t *resp;
    int ret, status;

    /* success */
    ret = h2o_read_command(argv[0], argv, &resp, &status);
    ok(ret == 0);
    if (ret == 0) {
        ok(WIFEXITED(status));
        ok(WEXITSTATUS(status) == 0);
        ok(h2o_memis(resp->bytes, resp->size, H2O_STRLIT("hello")));
        h2o_buffer_dispose(&resp);
    }

    /* exit status */
    setenv("READ_COMMAND_EXIT_STATUS", "75", 1);
    ret = h2o_read_command(argv[0], argv, &resp, &status);
    ok(ret == 0);
    if (ret == 0) {
        ok(WIFEXITED(status));
        ok(WEXITSTATUS(status) == 75);
        ok(h2o_memis(resp->bytes, resp->size, H2O_STRLIT("hello")));
        h2o_buffer_dispose(&resp);
    }
    unsetenv("READ_COMMAND_EXIT_STATUS");

    /* command not an executable */
    argv[0] = "t/00unit/assets";
    ret = h2o_read_command(argv[0], argv, &resp, &status);
    ok(ret != 0 || (ret == 0 && WIFEXITED(status) && WEXITSTATUS(status) == 127));
}