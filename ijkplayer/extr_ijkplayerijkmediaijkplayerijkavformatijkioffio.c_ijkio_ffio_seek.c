#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_5__ {int /*<<< orphan*/  inner; } ;
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ IjkURLContext ;
typedef  TYPE_2__ IjkIOFFioContext ;

/* Variables and functions */
 int ffurl_seek (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int64_t ijkio_ffio_seek(IjkURLContext *h, int64_t offset, int whence) {
    if (!h)
        return -1;

    IjkIOFFioContext *c= h->priv_data;

    if (!c || !c->inner)
        return -1;

    return ffurl_seek(c->inner, offset, whence);
}