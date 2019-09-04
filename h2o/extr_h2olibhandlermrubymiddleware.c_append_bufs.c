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
struct st_mruby_subreq_t {int /*<<< orphan*/  buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_buffer_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void append_bufs(struct st_mruby_subreq_t *subreq, h2o_iovec_t *inbufs, size_t inbufcnt)
{
    int i;
    for (i = 0; i != inbufcnt; ++i) {
        h2o_buffer_append(&subreq->buf, inbufs[i].base, inbufs[i].len);
    }
}