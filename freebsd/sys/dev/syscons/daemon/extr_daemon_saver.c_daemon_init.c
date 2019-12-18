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
typedef  int /*<<< orphan*/  video_adapter_t ;
struct TYPE_2__ {char* pr_hostname; int /*<<< orphan*/  pr_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  attr_mask ; 
 scalar_t__ blanked ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message ; 
 int messagelen ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 char* osrelease ; 
 char* ostype ; 
 TYPE_1__ prison0 ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int
daemon_init(video_adapter_t *adp)
{
	size_t hostlen;

	mtx_lock(&prison0.pr_mtx);
	for (;;) {
		hostlen = strlen(prison0.pr_hostname);
		mtx_unlock(&prison0.pr_mtx);
	
		messagelen = hostlen + 3 + strlen(ostype) + 1 +
		    strlen(osrelease);
		message = malloc(messagelen + 1, M_DEVBUF, M_WAITOK);
		mtx_lock(&prison0.pr_mtx);
		if (hostlen < strlen(prison0.pr_hostname)) {
			free(message, M_DEVBUF);
			continue;
		}
		break;
	}
	sprintf(message, "%s - %s %s", prison0.pr_hostname, ostype, osrelease);
	mtx_unlock(&prison0.pr_mtx);
	blanked = 0;
	attr_mask = ~0;

	return 0;
}