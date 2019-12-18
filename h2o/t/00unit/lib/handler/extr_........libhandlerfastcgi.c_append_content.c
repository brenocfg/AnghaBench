#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_4__* receiving; } ;
struct st_fcgi_generator_t {size_t leftsize; TYPE_1__ resp; } ;
struct TYPE_6__ {int /*<<< orphan*/ * base; } ;
typedef  TYPE_2__ h2o_iovec_t ;
struct TYPE_7__ {size_t size; } ;

/* Variables and functions */
 size_t SIZE_MAX ; 
 TYPE_2__ h2o_buffer_try_reserve (TYPE_4__**,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 

__attribute__((used)) static int append_content(struct st_fcgi_generator_t *generator, const void *src, size_t len)
{
    /* do not accumulate more than content-length bytes */
    if (generator->leftsize != SIZE_MAX) {
        if (generator->leftsize < len) {
            len = generator->leftsize;
            if (len == 0)
                return 0;
        }
        generator->leftsize -= len;
    }
    h2o_iovec_t reserved = h2o_buffer_try_reserve(&generator->resp.receiving, len);
    if (reserved.base == NULL) {
        return -1;
    }
    memcpy(reserved.base, src, len);
    generator->resp.receiving->size += len;
    return 0;
}