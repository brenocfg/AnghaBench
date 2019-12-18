#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ucl_parser {int /*<<< orphan*/  err; } ;
struct ucl_include_params {scalar_t__ must_exist; scalar_t__ soft_fail; int /*<<< orphan*/  allow_glob; } ;
typedef  int /*<<< orphan*/  globbuf ;
struct TYPE_5__ {size_t gl_pathc; scalar_t__* gl_pathv; } ;
typedef  TYPE_1__ glob_t ;
typedef  int /*<<< orphan*/  glob_pattern ;

/* Variables and functions */
 int PATH_MAX ; 
 scalar_t__ glob (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  globfree (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 size_t strlen (scalar_t__) ; 
 int /*<<< orphan*/  ucl_create_err (int /*<<< orphan*/ *,char*,char*) ; 
 int ucl_include_file_single (unsigned char const*,size_t,struct ucl_parser*,struct ucl_include_params*) ; 
 int /*<<< orphan*/  ucl_strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static bool
ucl_include_file (const unsigned char *data, size_t len,
		struct ucl_parser *parser, struct ucl_include_params *params)
{
	const unsigned char *p = data, *end = data + len;
	bool need_glob = false;
	int cnt = 0;
	char glob_pattern[PATH_MAX];
	size_t i;

#ifndef _WIN32
	if (!params->allow_glob) {
		return ucl_include_file_single (data, len, parser, params);
	}
	else {
		/* Check for special symbols in a filename */
		while (p != end) {
			if (*p == '*' || *p == '?') {
				need_glob = true;
				break;
			}
			p ++;
		}
		if (need_glob) {
			glob_t globbuf;
			memset (&globbuf, 0, sizeof (globbuf));
			ucl_strlcpy (glob_pattern, (const char *)data,
				(len + 1 < sizeof (glob_pattern) ? len + 1 : sizeof (glob_pattern)));
			if (glob (glob_pattern, 0, NULL, &globbuf) != 0) {
				return (!params->must_exist || false);
			}
			for (i = 0; i < globbuf.gl_pathc; i ++) {
				if (!ucl_include_file_single ((unsigned char *)globbuf.gl_pathv[i],
						strlen (globbuf.gl_pathv[i]), parser, params)) {
					if (params->soft_fail) {
						continue;
					}
					globfree (&globbuf);
					return false;
				}
				cnt ++;
			}
			globfree (&globbuf);

			if (cnt == 0 && params->must_exist) {
				ucl_create_err (&parser->err, "cannot match any files for pattern %s",
					glob_pattern);
				return false;
			}
		}
		else {
			return ucl_include_file_single (data, len, parser, params);
		}
	}
#else
	/* Win32 compilers do not support globbing. Therefore, for Win32,
	   treat allow_glob/need_glob as a NOOP and just return */
	return ucl_include_file_single (data, len, parser, params);
#endif

	return true;
}