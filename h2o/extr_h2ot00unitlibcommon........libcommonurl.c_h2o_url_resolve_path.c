#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t len; char* base; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 TYPE_1__ h2o_iovec_init (char*,size_t) ; 

void h2o_url_resolve_path(h2o_iovec_t *base, h2o_iovec_t *relative)
{
    size_t base_path_len = base->len, rel_path_offset = 0;

    if (relative->len != 0 && relative->base[0] == '/') {
        base_path_len = 0;
    } else {
        /* relative path */
        while (base->base[--base_path_len] != '/')
            ;
        while (rel_path_offset != relative->len) {
            if (relative->base[rel_path_offset] == '.') {
                if (relative->len - rel_path_offset >= 2 && relative->base[rel_path_offset + 1] == '.' &&
                    (relative->len - rel_path_offset == 2 || relative->base[rel_path_offset + 2] == '/')) {
                    if (base_path_len != 0) {
                        while (base->base[--base_path_len] != '/')
                            ;
                    }
                    rel_path_offset += relative->len - rel_path_offset == 2 ? 2 : 3;
                    continue;
                }
                if (relative->len - rel_path_offset == 1) {
                    rel_path_offset += 1;
                    continue;
                } else if (relative->base[rel_path_offset + 1] == '/') {
                    rel_path_offset += 2;
                    continue;
                }
            }
            break;
        }
        base_path_len += 1;
    }

    base->len = base_path_len;
    *relative = h2o_iovec_init(relative->base + rel_path_offset, relative->len - rel_path_offset);
}