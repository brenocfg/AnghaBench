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
struct addrinfo {int dummy; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int sl_cur; char** sl_str; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/ * ask ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct addrinfo**) ; 
 int* got ; 
 TYPE_1__* hosts ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int random () ; 
 int snprintf (char*,int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stats ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
resolvone(int n)
{
	char buf[1024];
	pthread_t self = pthread_self();
	size_t i = (random() & 0x0fffffff) % hosts->sl_cur;
	char *host = hosts->sl_str[i];
	struct addrinfo *res;
	int error, len;
	if (debug) {
		len = snprintf(buf, sizeof(buf), "%p: %d resolving %s %d\n",
			self, n, host, (int)i);
		(void)write(STDOUT_FILENO, buf, len);
	}
	error = getaddrinfo(host, NULL, NULL, &res);
	if (debug) {
		len = snprintf(buf, sizeof(buf), "%p: host %s %s\n",
			self, host, error ? "not found" : "ok");
		(void)write(STDOUT_FILENO, buf, len);
	}
	pthread_mutex_lock(&stats);
	ask[i]++;
	got[i] += error == 0;
	pthread_mutex_unlock(&stats);
	if (error == 0)
		freeaddrinfo(res);
}