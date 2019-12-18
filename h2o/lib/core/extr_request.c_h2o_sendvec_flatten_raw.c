#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ len; scalar_t__ raw; } ;
typedef  TYPE_1__ h2o_sendvec_t ;
typedef  int /*<<< orphan*/  h2o_req_t ;
struct TYPE_6__ {scalar_t__ len; int /*<<< orphan*/  base; } ;
typedef  TYPE_2__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

int h2o_sendvec_flatten_raw(h2o_sendvec_t *src, h2o_req_t *req, h2o_iovec_t dst, size_t off)
{
    assert(off + dst.len <= src->len);
    memcpy(dst.base, src->raw + off, dst.len);
    return 1;
}