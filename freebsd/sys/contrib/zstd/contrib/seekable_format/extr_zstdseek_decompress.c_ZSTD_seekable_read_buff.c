#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ pos; scalar_t__ size; scalar_t__ ptr; } ;
typedef  TYPE_1__ buffWrapper_t ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int ZSTD_seekable_read_buff(void* opaque, void* buffer, size_t n)
{
    buffWrapper_t* buff = (buffWrapper_t*) opaque;
    if (buff->pos + n > buff->size) return -1;
    memcpy(buffer, (const BYTE*)buff->ptr + buff->pos, n);
    buff->pos += n;
    return 0;
}