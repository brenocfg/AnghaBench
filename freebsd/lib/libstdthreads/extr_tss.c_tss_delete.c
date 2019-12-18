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
typedef  int /*<<< orphan*/  tss_t ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_key_delete (int /*<<< orphan*/ ) ; 

void
tss_delete(tss_t key)
{

	(void)pthread_key_delete(key);
}