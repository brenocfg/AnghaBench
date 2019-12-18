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
struct ntlm_buf {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  heim_ntlm_nt_key (char*,struct ntlm_buf*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rk_cloexec_file (int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 size_t strcspn (char*,char*) ; 
 char* strdup (char*) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static int
from_file(const char *fn, const char *target_domain,
	  char **username, struct ntlm_buf *key)
{
    char *str, buf[1024];
    FILE *f;

    f = fopen(fn, "r");
    if (f == NULL)
	return ENOENT;
    rk_cloexec_file(f);

    while (fgets(buf, sizeof(buf), f) != NULL) {
	char *d, *u, *p;
	buf[strcspn(buf, "\r\n")] = '\0';
	if (buf[0] == '#')
	    continue;
	str = NULL;
	d = strtok_r(buf, ":", &str);
	if (d && strcasecmp(target_domain, d) != 0)
	    continue;
	u = strtok_r(NULL, ":", &str);
	p = strtok_r(NULL, ":", &str);
	if (u == NULL || p == NULL)
	    continue;

	*username = strdup(u);

	heim_ntlm_nt_key(p, key);

	memset(buf, 0, sizeof(buf));
	fclose(f);
	return 0;
    }
    memset(buf, 0, sizeof(buf));
    fclose(f);
    return ENOENT;
}