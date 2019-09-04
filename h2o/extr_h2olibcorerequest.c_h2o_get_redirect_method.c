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
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 TYPE_1__ h2o_iovec_init (int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_memis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

h2o_iovec_t h2o_get_redirect_method(h2o_iovec_t method, int status)
{
    if (h2o_memis(method.base, method.len, H2O_STRLIT("POST")) && !(status == 307 || status == 308))
        method = h2o_iovec_init(H2O_STRLIT("GET"));
    return method;
}