#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_mem_alloc_shared (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static h2o_iovec_t dupref(const char *s)
{
    h2o_iovec_t ret;
    ret.len = strlen(s);
    ret.base = h2o_mem_alloc_shared(NULL, ret.len + 1, NULL);
    memcpy(ret.base, s, ret.len + 1);
    return ret;
}