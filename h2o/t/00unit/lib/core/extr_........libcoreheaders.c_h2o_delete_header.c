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
typedef  int ssize_t ;
struct TYPE_3__ {int size; scalar_t__ entries; } ;
typedef  TYPE_1__ h2o_headers_t ;
typedef  int /*<<< orphan*/  h2o_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 

ssize_t h2o_delete_header(h2o_headers_t *headers, ssize_t cursor)
{
    assert(cursor != -1);

    --headers->size;
    memmove(headers->entries + cursor, headers->entries + cursor + 1, sizeof(h2o_header_t) * (headers->size - cursor));

    return cursor;
}