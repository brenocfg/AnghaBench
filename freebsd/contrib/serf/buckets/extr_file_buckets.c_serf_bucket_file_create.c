#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
struct TYPE_9__ {TYPE_1__* read_baton; int /*<<< orphan*/  read; } ;
struct TYPE_7__ {TYPE_3__ databuf; int /*<<< orphan*/ * file; } ;
typedef  TYPE_1__ file_context_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_mmap_t ;
struct TYPE_8__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ apr_finfo_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_FINFO_SIZE ; 
 scalar_t__ APR_MMAP_CANDIDATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APR_MMAP_READ ; 
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  apr_file_name_get (char const**,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_mmap_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_stat (TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_reader ; 
 int /*<<< orphan*/  serf_bucket_allocator_get_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * serf_bucket_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* serf_bucket_mem_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * serf_bucket_mmap_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serf_bucket_type_file ; 
 int /*<<< orphan*/  serf_databuf_init (TYPE_3__*) ; 

serf_bucket_t *serf_bucket_file_create(
    apr_file_t *file,
    serf_bucket_alloc_t *allocator)
{
    file_context_t *ctx;
#if APR_HAS_MMAP
    apr_finfo_t finfo;
    const char *file_path;

    /* See if we'd be better off mmap'ing this file instead.
     *
     * Note that there is a failure case here that we purposely fall through:
     * if a file is buffered, apr_mmap will reject it.  However, on older
     * versions of APR, we have no way of knowing this - but apr_mmap_create
     * will check for this and return APR_EBADF.
     */
    apr_file_name_get(&file_path, file);
    apr_stat(&finfo, file_path, APR_FINFO_SIZE,
             serf_bucket_allocator_get_pool(allocator));
    if (APR_MMAP_CANDIDATE(finfo.size)) {
        apr_status_t status;
        apr_mmap_t *file_mmap;
        status = apr_mmap_create(&file_mmap, file, 0, finfo.size,
                                 APR_MMAP_READ,
                                 serf_bucket_allocator_get_pool(allocator));

        if (status == APR_SUCCESS) {
            return serf_bucket_mmap_create(file_mmap, allocator);
        }
    }
#endif

    /* Oh, well. */
    ctx = serf_bucket_mem_alloc(allocator, sizeof(*ctx));
    ctx->file = file;

    serf_databuf_init(&ctx->databuf);
    ctx->databuf.read = file_reader;
    ctx->databuf.read_baton = ctx;

    return serf_bucket_create(&serf_bucket_type_file, allocator, ctx);
}