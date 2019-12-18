#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * password; int /*<<< orphan*/ * user; int /*<<< orphan*/ * realm; int /*<<< orphan*/ * scheme; } ;
typedef  TYPE_1__ http_auth_params_t ;

/* Variables and functions */
 int /*<<< orphan*/  clean_http_auth_params (TYPE_1__*) ; 
 int /*<<< orphan*/  fetch_syserr () ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char*,char) ; 
 void* strdup (char const*) ; 

__attribute__((used)) static int
http_authfromenv(const char *p, http_auth_params_t *parms)
{
	int ret = -1;
	char *v, *ve;
	char *str = strdup(p);

	if (str == NULL) {
		fetch_syserr();
		return (-1);
	}
	v = str;

	if ((ve = strchr(v, ':')) == NULL)
		goto out;

	*ve = 0;
	if ((parms->scheme = strdup(v)) == NULL) {
		fetch_syserr();
		goto out;
	}
	v = ve + 1;

	if ((ve = strchr(v, ':')) == NULL)
		goto out;

	*ve = 0;
	if ((parms->realm = strdup(v)) == NULL) {
		fetch_syserr();
		goto out;
	}
	v = ve + 1;

	if ((ve = strchr(v, ':')) == NULL)
		goto out;

	*ve = 0;
	if ((parms->user = strdup(v)) == NULL) {
		fetch_syserr();
		goto out;
	}
	v = ve + 1;


	if ((parms->password = strdup(v)) == NULL) {
		fetch_syserr();
		goto out;
	}
	ret = 0;
out:
	if (ret == -1)
		clean_http_auth_params(parms);
	if (str)
		free(str);
	return (ret);
}