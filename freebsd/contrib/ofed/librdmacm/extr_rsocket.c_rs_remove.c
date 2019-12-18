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
struct rsocket {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  idm ; 
 int /*<<< orphan*/  idm_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mut ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rs_remove(struct rsocket *rs)
{
	pthread_mutex_lock(&mut);
	idm_clear(&idm, rs->index);
	pthread_mutex_unlock(&mut);
}