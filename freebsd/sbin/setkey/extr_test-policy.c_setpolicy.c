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
 int /*<<< orphan*/  free (char*) ; 
 int ipsec_get_policylen (char*) ; 
 int ipsec_set_policy (char*,int,char*) ; 
 char* ipsec_strerror () ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

char *setpolicy(char *req)
{
	int len;
	char *buf;

	if ((len = ipsec_get_policylen(req)) < 0) {
		printf("ipsec_get_policylen: %s\n", ipsec_strerror());
		return NULL;
	}

	if ((buf = malloc(len)) == NULL) {
		perror("malloc");
		return NULL;
	}

	if ((len = ipsec_set_policy(buf, len, req)) < 0) {
		printf("ipsec_set_policy: %s\n", ipsec_strerror());
		free(buf);
		return NULL;
	}

	return buf;
}