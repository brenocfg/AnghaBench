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
typedef  int /*<<< orphan*/  xo_string_node_t ;
typedef  int /*<<< orphan*/  xo_string_list_t ;

/* Variables and functions */
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xo_string_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xs_link ; 

__attribute__((used)) static inline void
xo_string_list_clean (xo_string_list_t *listp)
{
    xo_string_node_t *xsp;

    xo_string_list_init(listp);

    for (;;) {
	xsp = TAILQ_FIRST(listp);
        if (xsp == NULL)
            break;
        TAILQ_REMOVE(listp, xsp, xs_link);
	xo_free(xsp);
    }
}