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
struct sema {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sema_wait (struct sema*) ; 

void inline os_sema_unlock(struct sema *sema)
{
	sema_wait(sema);
}