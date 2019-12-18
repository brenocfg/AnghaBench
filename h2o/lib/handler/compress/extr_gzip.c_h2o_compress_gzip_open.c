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
struct TYPE_3__ {int /*<<< orphan*/  do_transform; } ;
struct st_gzip_context_t {TYPE_1__ super; int /*<<< orphan*/  zs; } ;
typedef  int /*<<< orphan*/  h2o_mem_pool_t ;
typedef  TYPE_1__ h2o_compress_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  WINDOW_BITS ; 
 int /*<<< orphan*/  Z_DEFAULT_STRATEGY ; 
 int /*<<< orphan*/  Z_DEFLATED ; 
 int /*<<< orphan*/  deflateInit2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_compress ; 
 struct st_gzip_context_t* gzip_open (int /*<<< orphan*/ *) ; 

h2o_compress_context_t *h2o_compress_gzip_open(h2o_mem_pool_t *pool, int quality)
{
    struct st_gzip_context_t *self = gzip_open(pool);
    self->super.do_transform = do_compress;
    /* Z_BEST_SPEED for on-the-fly compression, memlevel set to 8 as suggested by the manual */
    deflateInit2(&self->zs, quality, Z_DEFLATED, WINDOW_BITS, 8, Z_DEFAULT_STRATEGY);

    return &self->super;
}