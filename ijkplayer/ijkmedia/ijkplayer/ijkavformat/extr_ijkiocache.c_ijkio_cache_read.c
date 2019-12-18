#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_14__ {TYPE_1__* prot; } ;
struct TYPE_13__ {scalar_t__ cache_file_forwards_capacity; scalar_t__ read_logical_pos; int io_error; scalar_t__ file_logical_pos; int /*<<< orphan*/  file_mutex; int /*<<< orphan*/  cond_wakeup_file_background; scalar_t__ io_eof_reached; int /*<<< orphan*/  cond_wakeup_main; TYPE_5__* inner; scalar_t__ cache_file_close; } ;
struct TYPE_12__ {TYPE_3__* priv_data; } ;
struct TYPE_11__ {int (* url_seek ) (TYPE_5__*,scalar_t__,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ IjkURLContext ;
typedef  TYPE_3__ IjkIOCacheContext ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int IJKAVERROR (int /*<<< orphan*/ ) ; 
 int IJKAVERROR_EOF ; 
 int IJKAVERROR_EXIT ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  call_inject_statistic (TYPE_2__*) ; 
 scalar_t__ ijkio_cache_check_interrupt (TYPE_2__*) ; 
 int ijkio_cache_sync_read (TYPE_2__*,unsigned char*,int) ; 
 int ijkio_file_read (TYPE_2__*,unsigned char*,int) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_5__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int wrapped_url_read (TYPE_2__*,unsigned char*,int) ; 

__attribute__((used)) static int ijkio_cache_read(IjkURLContext *h, unsigned char *buf, int size) {
    IjkIOCacheContext *c = h->priv_data;
    int64_t          ret = 0;
    int          to_read = size;
    unsigned char  *dest = buf;
    int          to_copy = 0;

    if (!c || !c->inner || !c->inner->prot)
        return IJKAVERROR(ENOSYS);

    if (c->cache_file_close) {
        return wrapped_url_read(h, dest, to_read);
    }

    if (!c->cache_file_forwards_capacity) {
        ret = ijkio_cache_sync_read(h, buf, size);
        if (ret >= 0) {
            c->read_logical_pos += ret;
        }
        call_inject_statistic(h);
        return (int)ret;
    }

    pthread_mutex_lock(&c->file_mutex);
    while (to_read > 0) {
        if (ijkio_cache_check_interrupt(h)) {
            ret = IJKAVERROR_EXIT;
            break;
        }

        if (c->cache_file_close) {
            ret = c->inner->prot->url_seek(c->inner, c->read_logical_pos, SEEK_SET);
            if (ret < 0) {
                pthread_mutex_unlock(&c->file_mutex);
                return (int)ret;
            }

            to_copy  = wrapped_url_read(h, dest, to_read);
            to_read -= to_copy;
            ret      = size - to_read;
            pthread_mutex_unlock(&c->file_mutex);
            return (int)ret;
        }

        to_copy = ijkio_file_read(h, dest, to_read);
        if (to_copy > 0) {
            to_read             -= to_copy;
            ret                  = size - to_read;
            dest                += to_copy;
            c->read_logical_pos += to_copy;
            if (to_read <= 0)
                break;
        } else if (c->io_eof_reached) {
            if (ret <= 0) {
                if (c->io_error)
                    ret = c->io_error;
                else
                    ret = IJKAVERROR_EOF;
            }
            break;
        }
        pthread_cond_signal(&c->cond_wakeup_file_background);
        pthread_cond_wait(&c->cond_wakeup_main, &c->file_mutex);
    }

    if (ret != size || (!c->io_eof_reached && (c->file_logical_pos - c->read_logical_pos) <= c->cache_file_forwards_capacity)) {
        pthread_cond_signal(&c->cond_wakeup_file_background);
    }
    pthread_mutex_unlock(&c->file_mutex);
    return (int)ret;
}