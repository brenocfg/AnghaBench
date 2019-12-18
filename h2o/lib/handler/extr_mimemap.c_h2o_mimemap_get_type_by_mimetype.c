#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  khiter_t ;
struct TYPE_13__ {size_t len; char* base; } ;
struct TYPE_10__ {TYPE_4__ mimetype; } ;
struct TYPE_11__ {TYPE_1__ data; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ h2o_mimemap_type_t ;
struct TYPE_12__ {int /*<<< orphan*/  typeset; } ;
typedef  TYPE_3__ h2o_mimemap_t ;
typedef  TYPE_4__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_MIMEMAP_TYPE_MIMETYPE ; 
 int /*<<< orphan*/  kh_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kh_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* kh_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typeset ; 

h2o_mimemap_type_t *h2o_mimemap_get_type_by_mimetype(h2o_mimemap_t *mimemap, h2o_iovec_t mime, int exact_match_only)
{
    h2o_mimemap_type_t key = {H2O_MIMEMAP_TYPE_MIMETYPE};
    khiter_t iter;
    size_t type_end_at;

    /* exact match */
    key.data.mimetype = mime;
    if ((iter = kh_get(typeset, mimemap->typeset, &key)) != kh_end(mimemap->typeset))
        return kh_key(mimemap->typeset, iter);

    if (!exact_match_only) {
        /* determine the end of the type */
        for (type_end_at = 0; type_end_at != mime.len; ++type_end_at)
            if (mime.base[type_end_at] == ';' || mime.base[type_end_at] == ' ')
                goto HasAttributes;
    }
    return NULL;

HasAttributes:
    /* perform search without attributes */
    key.data.mimetype.len = type_end_at;
    if ((iter = kh_get(typeset, mimemap->typeset, &key)) != kh_end(mimemap->typeset))
        return kh_key(mimemap->typeset, iter);

    return NULL;
}