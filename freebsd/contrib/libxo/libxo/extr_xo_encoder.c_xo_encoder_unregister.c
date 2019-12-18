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
typedef  int /*<<< orphan*/  xo_encoder_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xe_link ; 
 int /*<<< orphan*/ * xo_encoder_find (char const*) ; 
 int /*<<< orphan*/  xo_encoder_setup () ; 
 int /*<<< orphan*/  xo_encoders ; 
 int /*<<< orphan*/  xo_free (int /*<<< orphan*/ *) ; 

void
xo_encoder_unregister (const char *name)
{
    xo_encoder_setup();

    xo_encoder_node_t *xep = xo_encoder_find(name);
    if (xep) {
	TAILQ_REMOVE(&xo_encoders, xep, xe_link);
	xo_free(xep);
    }
}