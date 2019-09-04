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
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ index_type ;
struct TYPE_3__ {scalar_t__ start_row; scalar_t__ effective_num_rows; } ;
typedef  TYPE_1__ ImageRef ;

/* Variables and functions */

__attribute__((used)) static inline bool
ref_within_region(ImageRef *ref, index_type margin_top, index_type margin_bottom) {
    return ref->start_row >= (int32_t)margin_top && ref->start_row + ref->effective_num_rows <= margin_bottom;
}