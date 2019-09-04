#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tl_query_header {int /*<<< orphan*/  ref_cnt; } ;

/* Variables and functions */

struct tl_query_header *tl_query_header_dup (struct tl_query_header *h) {
  h->ref_cnt ++;
  return h;
}