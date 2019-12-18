#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  EVF_READ ; 
 int /*<<< orphan*/  EVF_TIMER ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TEST_PORT ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  accept_condvar ; 
 int /*<<< orphan*/  accept_mutex ; 
 int /*<<< orphan*/  acceptor_callback ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  echoer ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  mevent_add (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tevp ; 
 int /*<<< orphan*/  timer_callback ; 

__attribute__((used)) static void *
acceptor(void *param)
{
	struct sockaddr_in sin;
	pthread_t tid;
	int news;
	int s;
	static int first;

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("cannot create socket");
		exit(4);
	}

	sin.sin_len = sizeof(sin);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(TEST_PORT);

	if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		perror("cannot bind socket");
		exit(4);
	}

	if (listen(s, 1) < 0) {
		perror("cannot listen socket");
		exit(4);
	}

	(void) mevent_add(s, EVF_READ, acceptor_callback, NULL);

	pthread_mutex_lock(&accept_mutex);

	while (!pthread_cond_wait(&accept_condvar, &accept_mutex)) {
		news = accept(s, NULL, NULL);
		if (news < 0) {
			perror("accept error");
		} else {
			static int first = 1;

			if (first) {
				/*
				 * Start a timer
				 */
				first = 0;
				tevp = mevent_add(1, EVF_TIMER, timer_callback,
						  NULL);
			}

			printf("incoming connection, spawning thread\n");
			pthread_create(&tid, NULL, echoer,
				       (void *)(uintptr_t)news);
		}
	}

	return (NULL);
}