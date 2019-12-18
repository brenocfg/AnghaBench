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
 int /*<<< orphan*/  log_report (char*,char const*,char const*,...) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 char* strtok_r (char*,char*,char**) ; 
 long strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void subn_verify_vlarb(char **vlarb, const char *prefix,
			      const char *suffix)
{
	char *str, *tok, *end, *ptr;
	int count = 0;

	if (*vlarb == NULL)
		return;

	str = strdup(*vlarb);

	tok = strtok_r(str, ",\n", &ptr);
	while (tok) {
		char *vl_str, *weight_str;

		vl_str = tok;
		weight_str = strchr(tok, ':');

		if (weight_str) {
			long vl, weight;

			*weight_str = '\0';
			weight_str++;

			vl = strtol(vl_str, &end, 0);

			if (*end)
				log_report(" Warning: Cached Option "
					   "%s_vlarb_%s:vl=%s"
					   " improperly formatted\n",
					   prefix, suffix, vl_str);
			else if (vl < 0 || vl > 14)
				log_report(" Warning: Cached Option "
					   "%s_vlarb_%s:vl=%ld out of range\n",
					   prefix, suffix, vl);

			weight = strtol(weight_str, &end, 0);

			if (*end)
				log_report(" Warning: Cached Option "
					   "%s_vlarb_%s:weight=%s "
					   "improperly formatted\n",
					   prefix, suffix, weight_str);
			else if (weight < 0 || weight > 255)
				log_report(" Warning: Cached Option "
					   "%s_vlarb_%s:weight=%ld "
					   "out of range\n",
					   prefix, suffix, weight);
		} else
			log_report(" Warning: Cached Option "
				   "%s_vlarb_%s:vl:weight=%s "
				   "improperly formatted\n",
				   prefix, suffix, tok);

		count++;
		tok = strtok_r(NULL, ",\n", &ptr);
	}

	if (count > 64)
		log_report(" Warning: Cached Option %s_vlarb_%s: > 64 listed:"
			   " excess vl:weight pairs will be dropped\n",
			   prefix, suffix);

	free(str);
}