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
typedef  int uint32_t ;

/* Variables and functions */
 int IB_PC_FIRST_F ; 
 int IB_PC_LAST_F ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  mad_encode_field (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  mad_field_name (int) ; 
 char* realloc (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char* threshold_str ; 
 int /*<<< orphan*/  thresholds ; 

__attribute__((used)) static void set_thres(char *name, uint32_t val)
{
	int f;
	int n;
	char tmp[256];
	for (f = IB_PC_FIRST_F; f <= IB_PC_LAST_F; f++) {
		if (strcmp(name, mad_field_name(f)) == 0) {
			mad_encode_field(thresholds, f, &val);
			snprintf(tmp, 255, "[%s = %u]", name, val);
			threshold_str = realloc(threshold_str,
					strlen(threshold_str)+strlen(tmp)+1);
			if (!threshold_str) {
				fprintf(stderr, "Failed to allocate memory: "
					"%s\n", strerror(errno));
				exit(1);
			}
			n = strlen(threshold_str);
			strcpy(threshold_str+n, tmp);
		}
	}
}