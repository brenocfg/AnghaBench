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
struct pthread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct pthread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hle ; 

void
_thr_hash_remove(struct pthread *thread)
{
	LIST_REMOVE(thread, hle);
}