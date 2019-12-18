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
struct TYPE_3__ {int len; char* base; } ;
typedef  TYPE_1__ h2o_iovec_t ;
typedef  int /*<<< orphan*/  alphanum ;

/* Variables and functions */
 int h2o_rand () ; 

__attribute__((used)) static void gen_rand_string(h2o_iovec_t *s)
{
    int i;
    static const char alphanum[] = "0123456789"
                                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                   "abcdefghijklmnopqrstuvwxyz";

    for (i = 0; i < s->len; ++i) {
        s->base[i] = alphanum[h2o_rand() % (sizeof(alphanum) - 1)];
    }

    s->base[s->len] = 0;
}