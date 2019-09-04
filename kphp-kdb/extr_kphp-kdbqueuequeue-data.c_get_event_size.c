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
struct TYPE_3__ {int /*<<< orphan*/  data_len; } ;
typedef  TYPE_1__ event ;

/* Variables and functions */
 size_t get_event_size_d (int /*<<< orphan*/ ) ; 

inline size_t get_event_size (event *e) {
  return get_event_size_d (e->data_len);
}