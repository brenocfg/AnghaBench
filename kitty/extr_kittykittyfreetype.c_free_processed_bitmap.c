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
struct TYPE_3__ {int needs_free; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ ProcessedBitmap ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
free_processed_bitmap(ProcessedBitmap *bm) {
    if (bm->needs_free) {
        bm->needs_free = false;
        free(bm->buf); bm->buf = NULL;
    }
}