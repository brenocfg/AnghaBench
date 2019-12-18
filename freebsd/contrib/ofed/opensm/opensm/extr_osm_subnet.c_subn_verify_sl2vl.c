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
 int /*<<< orphan*/  log_report (char*,char const*,...) ; 
 char* strdup (char*) ; 
 char* strtok_r (char*,char*,char**) ; 
 long strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void subn_verify_sl2vl(char **sl2vl, const char *prefix)
{
	char *str, *tok, *end, *ptr;
	int count = 0;

	if (*sl2vl == NULL)
		return;

	str = strdup(*sl2vl);

	tok = strtok_r(str, ",\n", &ptr);
	while (tok) {
		long vl = strtol(tok, &end, 0);

		if (*end)
			log_report(" Warning: Cached Option %s_sl2vl:vl=%s "
				   "improperly formatted\n", prefix, tok);
		else if (vl < 0 || vl > 15)
			log_report(" Warning: Cached Option %s_sl2vl:vl=%ld "
				   "out of range\n", prefix, vl);

		count++;
		tok = strtok_r(NULL, ",\n", &ptr);
	}

	if (count < 16)
		log_report(" Warning: Cached Option %s_sl2vl: < 16 VLs "
			   "listed\n", prefix);
	else if (count > 16)
		log_report(" Warning: Cached Option %s_sl2vl: > 16 listed: "
			   "excess VLs will be dropped\n", prefix);

	free(str);
}