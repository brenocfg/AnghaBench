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
struct TYPE_3__ {scalar_t__ mapped_file_sz; int /*<<< orphan*/ * mapped_file; int /*<<< orphan*/ * buf; scalar_t__ buf_capacity; scalar_t__ buf_used; } ;
typedef  TYPE_1__ LoadData ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static inline void
free_load_data(LoadData *ld) {
    free(ld->buf); ld->buf_used = 0; ld->buf_capacity = 0;
    ld->buf = NULL;

    if (ld->mapped_file) munmap(ld->mapped_file, ld->mapped_file_sz);
    ld->mapped_file = NULL; ld->mapped_file_sz = 0;
}