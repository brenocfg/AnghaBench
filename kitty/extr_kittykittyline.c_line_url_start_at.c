#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ index_type ;
struct TYPE_6__ {scalar_t__ xnum; } ;
typedef  TYPE_1__ Line ;

/* Variables and functions */
 scalar_t__ MAX_URL_SCHEME_LEN ; 
 scalar_t__ MIN_URL_LEN ; 
 scalar_t__ find_colon_slash (TYPE_1__*,scalar_t__,scalar_t__) ; 
 scalar_t__ has_url_beyond (TYPE_1__*,scalar_t__) ; 
 scalar_t__ has_url_prefix_at (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__*) ; 

index_type
line_url_start_at(Line *self, index_type x) {
    // Find the starting cell for a URL that contains the position x. A URL is defined as
    // known-prefix://url-chars. If no URL is found self->xnum is returned.
    if (x >= self->xnum || self->xnum <= MIN_URL_LEN + 3) return self->xnum;
    index_type ds_pos = 0, t;
    // First look for :// ahead of x
    if (self->xnum - x > MAX_URL_SCHEME_LEN + 3) ds_pos = find_colon_slash(self, x + MAX_URL_SCHEME_LEN + 3, x < 2 ? 0 : x - 2);
    if (ds_pos != 0 && has_url_beyond(self, ds_pos)) {
        if (has_url_prefix_at(self, ds_pos, ds_pos > x ? ds_pos - x: 0, &t)) return t;
    }
    ds_pos = find_colon_slash(self, x, 0);
    if (ds_pos == 0 || self->xnum < ds_pos + MIN_URL_LEN + 3 || !has_url_beyond(self, ds_pos)) return self->xnum;
    if (has_url_prefix_at(self, ds_pos, 0, &t)) return t;
    return self->xnum;
}