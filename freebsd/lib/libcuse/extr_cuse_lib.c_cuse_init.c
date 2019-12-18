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
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;

/* Variables and functions */
 int CUSE_ERR_INVALID ; 
 int CUSE_ERR_NOT_LOADED ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PTHREAD_MUTEX_RECURSIVE ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 scalar_t__ f_cuse ; 
 scalar_t__ feature_present (char*) ; 
 int /*<<< orphan*/  h_cuse ; 
 int /*<<< orphan*/  h_cuse_entered ; 
 int /*<<< orphan*/  m_cuse ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutexattr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutexattr_settype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
cuse_init(void)
{
	pthread_mutexattr_t attr;

	f_cuse = open("/dev/cuse", O_RDWR);
	if (f_cuse < 0) {
		if (feature_present("cuse") == 0)
			return (CUSE_ERR_NOT_LOADED);
		else
			return (CUSE_ERR_INVALID);
	}
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m_cuse, &attr);

	TAILQ_INIT(&h_cuse);
	TAILQ_INIT(&h_cuse_entered);

	return (0);
}