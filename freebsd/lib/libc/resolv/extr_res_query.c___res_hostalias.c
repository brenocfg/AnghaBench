#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* res_state ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int options; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int RES_NOALIASES ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char* getenv (char*) ; 
 scalar_t__ issetugid () ; 
 scalar_t__ isspace (unsigned char) ; 
 int ns_samename (char*,char const*) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 

const char *
res_hostalias(const res_state statp, const char *name, char *dst, size_t siz) {
	char *file, *cp1, *cp2;
	char buf[BUFSIZ];
	FILE *fp;

	if (statp->options & RES_NOALIASES)
		return (NULL);
	if (issetugid())
		return (NULL);
	file = getenv("HOSTALIASES");
	if (file == NULL || (fp = fopen(file, "re")) == NULL)
		return (NULL);
	setbuf(fp, NULL);
	buf[sizeof(buf) - 1] = '\0';
	while (fgets(buf, sizeof(buf), fp)) {
		for (cp1 = buf; *cp1 && !isspace((unsigned char)*cp1); ++cp1)
			;
		if (!*cp1)
			break;
		*cp1 = '\0';
		if (ns_samename(buf, name) == 1) {
			while (isspace((unsigned char)*++cp1))
				;
			if (!*cp1)
				break;
			for (cp2 = cp1 + 1; *cp2 &&
			     !isspace((unsigned char)*cp2); ++cp2)
				;
			*cp2 = '\0';
			strncpy(dst, cp1, siz - 1);
			dst[siz - 1] = '\0';
			fclose(fp);
			return (dst);
		}
	}
	fclose(fp);
	return (NULL);
}