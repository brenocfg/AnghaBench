#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * tqh_last; } ;
typedef  TYPE_1__ xo_encoder_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (TYPE_1__*) ; 

__attribute__((used)) static void
xo_encoder_list_init (xo_encoder_list_t *listp)
{
    if (listp->tqh_last == NULL)
	TAILQ_INIT(listp);
}