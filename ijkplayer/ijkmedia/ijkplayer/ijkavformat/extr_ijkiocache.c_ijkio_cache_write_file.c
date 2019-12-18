#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_17__ {TYPE_2__* prot; } ;
struct TYPE_16__ {scalar_t__ logical_pos; scalar_t__ size; } ;
struct TYPE_15__ {scalar_t__ file_logical_pos; scalar_t__ file_logical_end; int io_eof_reached; scalar_t__ logical_size; scalar_t__ file_inner_pos; scalar_t__ async_open; int io_error; int /*<<< orphan*/  file_mutex; int /*<<< orphan*/  cond_wakeup_file_background; int /*<<< orphan*/ * cache_count_bytes; TYPE_6__* inner; int /*<<< orphan*/  inner_options; int /*<<< orphan*/  inner_flags; int /*<<< orphan*/  inner_url; TYPE_1__* tree_info; } ;
struct TYPE_14__ {TYPE_4__* priv_data; } ;
struct TYPE_13__ {scalar_t__ (* url_seek ) (TYPE_6__*,scalar_t__,int /*<<< orphan*/ ) ;scalar_t__ (* url_read ) (TYPE_6__*,unsigned char*,int) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_3__ IjkURLContext ;
typedef  TYPE_4__ IjkIOCacheContext ;
typedef  TYPE_5__ IjkCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 scalar_t__ FFMIN (scalar_t__,int) ; 
 scalar_t__ IJKAVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ add_entry (TYPE_3__*,unsigned char*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cmp ; 
 TYPE_5__* ijk_av_tree_find (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,void**) ; 
 scalar_t__ ijkio_cache_io_open (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_6__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_6__*,unsigned char*,int) ; 

__attribute__((used)) static int64_t ijkio_cache_write_file(IjkURLContext *h) {
    IjkIOCacheContext *c= h->priv_data;
    int64_t r;
    unsigned char buf[4096] = {0};
    int to_read = 4096;
    int64_t to_copy = (int64_t)to_read;

    IjkCacheEntry *root = NULL ,*l_entry = NULL, *r_entry = NULL, *next[2] = {NULL, NULL};

    if (!c || !c->inner || !c->inner->prot)
        return IJKAVERROR(ENOSYS);

    root = ijk_av_tree_find(c->tree_info->root, &c->file_logical_pos, cmp, (void**)next);

    if (!root)
        l_entry = next[0];

    if (l_entry) {
        int64_t in_block_pos = c->file_logical_pos - l_entry->logical_pos;
        assert(l_entry->logical_pos <= c->file_logical_pos);
        if (in_block_pos < l_entry->size) {
            c->file_logical_pos = l_entry->logical_pos + l_entry->size;
        }
    } else if (root) {
        int64_t in_block_pos = c->file_logical_pos - root->logical_pos;
        assert(root->logical_pos <= c->file_logical_pos);
        if (in_block_pos < root->size) {
            c->file_logical_pos = root->logical_pos + root->size;
        }
    }

    r_entry = next[1];

    if (r_entry) {
        to_copy = r_entry->logical_pos - c->file_logical_pos;
        to_copy = FFMIN(to_copy, to_read);
    }

    if (to_copy == 0) {
        return 0;
    }

    if (c->file_logical_end > 0 && c->file_logical_pos == c->file_logical_end) {
        c->io_eof_reached = 1;
        return 0;
    }

    if (c->file_logical_pos >= c->logical_size) {
        c->io_eof_reached = 1;
        return 0;
    }
    if (c->file_logical_pos != c->file_inner_pos) {
        if (c->async_open > 0) {
            r = ijkio_cache_io_open(h, c->inner_url, c->inner_flags, &c->inner_options);
            if (r != 0) {
                c->io_eof_reached = 1;
                c->io_error = (int)r;
                return r;
            }
            c->async_open = 0;
        }

        r = c->inner->prot->url_seek(c->inner, c->file_logical_pos, SEEK_SET);

        if (r < 0) {
            c->io_eof_reached = 1;
            if (c->file_logical_end == c->file_logical_pos) {
                c->file_inner_pos = c->file_logical_end;
            }
            return r;
        }
        c->file_inner_pos = r;
    }
    if (c->async_open > 0) {
        r = ijkio_cache_io_open(h, c->inner_url, c->inner_flags, &c->inner_options);
        if (r != 0) {
            c->io_eof_reached = 1;
            c->io_error = (int)r;
            return r;
        }
        c->async_open = 0;
    }
    r = c->inner->prot->url_read(c->inner, buf, (int)to_copy);
    if (r == 0 && to_copy > 0) {
        c->file_logical_end = c->file_logical_pos;
    }
    if (r <= 0) {
        c->io_eof_reached = 1;
        c->io_error = (int)r;
        return r;
    }
    *c->cache_count_bytes += r;
    c->file_inner_pos += r;

    pthread_mutex_lock(&c->file_mutex);
    r = add_entry(h, buf, (int)r);

    if (r > 0) {
        c->file_logical_pos += r;
        pthread_cond_signal(&c->cond_wakeup_file_background);
    }
    pthread_mutex_unlock(&c->file_mutex);

    return r;
}