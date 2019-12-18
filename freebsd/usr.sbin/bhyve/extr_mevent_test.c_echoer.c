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
struct mevent {int dummy; } ;
struct esync {int /*<<< orphan*/  e_cond; int /*<<< orphan*/  e_mt; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  EVF_READ ; 
 int /*<<< orphan*/  echoer_callback ; 
 int /*<<< orphan*/  exit (int) ; 
 struct mevent* mevent_add (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct esync*) ; 
 int /*<<< orphan*/  mevent_delete_close (struct mevent*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

__attribute__((used)) static void *
echoer(void *param)
{
	struct esync sync;
	struct mevent *mev;
	char buf[128];
	int fd = (int)(uintptr_t) param;
	int len;

	pthread_mutex_init(&sync.e_mt, NULL);
	pthread_cond_init(&sync.e_cond, NULL);

	pthread_mutex_lock(&sync.e_mt);

	mev = mevent_add(fd, EVF_READ, echoer_callback, &sync);
	if (mev == NULL) {
		printf("Could not allocate echoer event\n");
		exit(4);
	}

	while (!pthread_cond_wait(&sync.e_cond, &sync.e_mt)) {
		len = read(fd, buf, sizeof(buf));
		if (len > 0) {
			write(fd, buf, len);
			write(0, buf, len);
		} else {
			break;
		}
	}

	mevent_delete_close(mev);

	pthread_mutex_unlock(&sync.e_mt);
	pthread_mutex_destroy(&sync.e_mt);
	pthread_cond_destroy(&sync.e_cond);

	return (NULL);
}