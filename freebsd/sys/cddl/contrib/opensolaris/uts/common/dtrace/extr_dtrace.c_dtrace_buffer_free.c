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
struct TYPE_3__ {scalar_t__ dtb_size; int dtb_flags; int /*<<< orphan*/ * dtb_xamot; int /*<<< orphan*/ * dtb_tomax; } ;
typedef  TYPE_1__ dtrace_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int DTRACEBUF_NOSWITCH ; 
 int NCPU ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
dtrace_buffer_free(dtrace_buffer_t *bufs)
{
	int i;

	for (i = 0; i < NCPU; i++) {
		dtrace_buffer_t *buf = &bufs[i];

		if (buf->dtb_tomax == NULL) {
			ASSERT(buf->dtb_xamot == NULL);
			ASSERT(buf->dtb_size == 0);
			continue;
		}

		if (buf->dtb_xamot != NULL) {
			ASSERT(!(buf->dtb_flags & DTRACEBUF_NOSWITCH));
			kmem_free(buf->dtb_xamot, buf->dtb_size);
		}

		kmem_free(buf->dtb_tomax, buf->dtb_size);
		buf->dtb_size = 0;
		buf->dtb_tomax = NULL;
		buf->dtb_xamot = NULL;
	}
}