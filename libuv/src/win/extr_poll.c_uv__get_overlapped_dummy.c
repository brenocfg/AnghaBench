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
typedef  int /*<<< orphan*/  OVERLAPPED ;

/* Variables and functions */
 int /*<<< orphan*/  overlapped_dummy_ ; 
 int /*<<< orphan*/  overlapped_dummy_init_guard_ ; 
 int /*<<< orphan*/  uv__init_overlapped_dummy ; 
 int /*<<< orphan*/  uv_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OVERLAPPED* uv__get_overlapped_dummy(void) {
  uv_once(&overlapped_dummy_init_guard_, uv__init_overlapped_dummy);
  return &overlapped_dummy_;
}