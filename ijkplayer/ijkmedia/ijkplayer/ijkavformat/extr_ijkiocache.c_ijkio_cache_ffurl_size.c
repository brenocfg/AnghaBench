#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_12__ {TYPE_1__* prot; } ;
struct TYPE_11__ {TYPE_4__* inner; } ;
struct TYPE_10__ {TYPE_3__* priv_data; } ;
struct TYPE_9__ {scalar_t__ (* url_seek ) (TYPE_4__*,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ IjkURLContext ;
typedef  TYPE_3__ IjkIOCacheContext ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 scalar_t__ IJKAVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IJKAVSEEK_SIZE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ stub1 (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stub4 (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t ijkio_cache_ffurl_size(IjkURLContext *h) {
    int64_t pos, size;
    IjkIOCacheContext *c= ((IjkURLContext *)h)->priv_data;
    if (!c || !c->inner || !c->inner->prot)
        return IJKAVERROR(ENOSYS);
    size = c->inner->prot->url_seek(c->inner, 0, IJKAVSEEK_SIZE);
    if (size < 0) {
        pos = c->inner->prot->url_seek(c->inner, 0, SEEK_CUR);
        if ((size = c->inner->prot->url_seek(c->inner, -1, SEEK_END)) < 0)
            return size;
        size++;
        c->inner->prot->url_seek(c->inner, pos, SEEK_SET);
    }
    return size;
}