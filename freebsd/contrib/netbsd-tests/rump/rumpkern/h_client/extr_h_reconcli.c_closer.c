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

/* Variables and functions */
 int /*<<< orphan*/  closefrom (int) ; 
 int /*<<< orphan*/  closercv ; 
 int /*<<< orphan*/  closermtx ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quit ; 
 int random () ; 
 scalar_t__ riseandwhine ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void *
closer(void *arg)
{

	pthread_mutex_lock(&closermtx);
	while (!quit) {
		while (!riseandwhine)
			pthread_cond_wait(&closercv, &closermtx);
		riseandwhine = 0;
		pthread_mutex_unlock(&closermtx);

		/* try to catch a random slot */
		usleep(random() % 100000);

		/*
		 * wide-angle disintegration beam, but takes care
		 * of the client rumpkernel communication socket.
		 */
		closefrom(3);

		pthread_mutex_lock(&closermtx);
	}
	pthread_mutex_unlock(&closermtx);

	return NULL;
}