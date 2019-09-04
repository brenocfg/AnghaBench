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
typedef  int /*<<< orphan*/  h2o_mem_pool_t ;
typedef  int /*<<< orphan*/  h2o_iovec_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* transform ) (TYPE_1__*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **,size_t*) ;} ;
typedef  TYPE_1__ h2o_compress_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  Z_BEST_SPEED ; 
 int /*<<< orphan*/  check_result (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__* h2o_compress_gzip_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mem_clear_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mem_init_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **,size_t*) ; 

void test_gzip_simple(void)
{
    h2o_mem_pool_t pool;
    h2o_iovec_t inbuf, *outbufs;
    size_t outbufcnt;

    h2o_mem_init_pool(&pool);

    h2o_compress_context_t *compressor = h2o_compress_gzip_open(&pool, Z_BEST_SPEED);
    inbuf = h2o_iovec_init(H2O_STRLIT("hello world"));
    compressor->transform(compressor, &inbuf, 1, 1, &outbufs, &outbufcnt);

    check_result(outbufs, outbufcnt, H2O_STRLIT("hello world"));

    h2o_mem_clear_pool(&pool);
}