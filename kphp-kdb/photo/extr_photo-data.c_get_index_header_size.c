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
typedef  int /*<<< orphan*/  user_index_data ;
struct TYPE_3__ {int user_cnt; } ;
typedef  TYPE_1__ index_header ;

/* Variables and functions */

long long get_index_header_size (index_header *header) {
  return sizeof (index_header) + sizeof (user_index_data) * (header->user_cnt + 1);
}