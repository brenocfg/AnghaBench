#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cache_uri {scalar_t__ uri_md5_h0; scalar_t__ data; } ;
struct TYPE_3__ {scalar_t__* h; } ;
struct TYPE_4__ {int computed; TYPE_1__ uri_md5; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__ get_uri_f_last_md5 ; 
 int /*<<< orphan*/  uri2md5 (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  uri2md5_extra_calls ; 
 scalar_t__ uri_off ; 

__attribute__((used)) static void compute_get_uri_f_last_md5 (const struct cache_uri *U) {
  if (!get_uri_f_last_md5.computed) {
    uri2md5 (U->data + uri_off, &get_uri_f_last_md5.uri_md5);
    uri2md5_extra_calls++;
    get_uri_f_last_md5.computed = 1;
    assert (U->uri_md5_h0 == get_uri_f_last_md5.uri_md5.h[0]);
  }
}