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
#define  METHOD_GETADDRINFO 130 
#define  METHOD_GETHOSTBY 129 
#define  METHOD_GETIPNODEBY 128 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/ * ask ; 
 int* got ; 
 TYPE_1__* hosts ; 
 int method ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int random () ; 
 int resolv_getaddrinfo (int /*<<< orphan*/ ,char*,size_t) ; 
 int resolv_gethostby (int /*<<< orphan*/ ,char*) ; 
 int resolv_getipnodeby (int /*<<< orphan*/ ,char*) ; 
 int snprintf (char*,int,char*,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  stats ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
resolvone(int n)
{
	char buf[1024];
	pthread_t self = pthread_self();
	size_t i = (random() & 0x0fffffff) % hosts->sl_cur;
	char *host = hosts->sl_str[i];
	struct addrinfo hints, *res;
	int error, len;

	len = snprintf(buf, sizeof(buf), "%p: %d resolving %s %d\n",
	    self, n, host, (int)i);
	(void)write(STDOUT_FILENO, buf, len);
	switch (method) {
	case METHOD_GETADDRINFO:
		error = resolv_getaddrinfo(self, host, i);
		break;
	case METHOD_GETHOSTBY:
		error = resolv_gethostby(self, host);
		break;
	case METHOD_GETIPNODEBY:
		error = resolv_getipnodeby(self, host);
		break;
	default:
		break;
	}
	pthread_mutex_lock(&stats);
	ask[i]++;
	got[i] += error == 0;
	pthread_mutex_unlock(&stats);
}