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
struct expected_t {int is_critical; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int h2o_memis (char const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_path(void *ctx, const char *path, size_t path_len, int is_critical)
{
    struct expected_t **expected = ctx;
    ok(h2o_memis(path, path_len, (*expected)->path, strlen((*expected)->path)));
    ok(is_critical == (*expected)->is_critical);
    ++*expected;
}