#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lcbuf ;
typedef  scalar_t__ khiter_t ;
typedef  int /*<<< orphan*/  h2o_mimemap_type_t ;
struct TYPE_5__ {int /*<<< orphan*/ * default_type; int /*<<< orphan*/  extmap; } ;
typedef  TYPE_1__ h2o_mimemap_t ;
struct TYPE_6__ {int len; int /*<<< orphan*/  base; } ;
typedef  TYPE_2__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  extmap ; 
 int /*<<< orphan*/  h2o_strtolower (char*,int) ; 
 scalar_t__ kh_end (int /*<<< orphan*/ ) ; 
 scalar_t__ kh_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * kh_val (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

h2o_mimemap_type_t *h2o_mimemap_get_type_by_extension(h2o_mimemap_t *mimemap, h2o_iovec_t ext)
{
    char lcbuf[256];

    if (0 < ext.len && ext.len < sizeof(lcbuf)) {
        memcpy(lcbuf, ext.base, ext.len);
        h2o_strtolower(lcbuf, ext.len);
        lcbuf[ext.len] = '\0';
        khiter_t iter = kh_get(extmap, mimemap->extmap, lcbuf);
        if (iter != kh_end(mimemap->extmap))
            return kh_val(mimemap->extmap, iter);
    }
    return mimemap->default_type;
}