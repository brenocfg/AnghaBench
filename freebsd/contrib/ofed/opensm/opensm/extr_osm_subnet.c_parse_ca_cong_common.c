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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ IB_CA_CONG_ENTRY_DATA_SIZE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_report (char*) ; 
 int /*<<< orphan*/  null_str ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 char* strdup (char*) ; 
 char* strtok_r (char*,char*,char**) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_ca_cong_common(char *p_val_str, uint8_t *sl, unsigned int *val_offset) {
	char *new, *lasts, *sl_str, *val_str;
	uint8_t sltmp;

	new = strcmp(null_str, p_val_str) ? strdup(p_val_str) : NULL;
	if (!new)
		return -1;

	sl_str = strtok_r(new, " \t", &lasts);
	val_str = strtok_r(NULL, " \t", &lasts);

	if (!val_str) {
		log_report("value must be specified in addition to SL\n");
		free(new);
		return -1;
	}

	sltmp = strtoul(sl_str, NULL, 0);
	if (sltmp >= IB_CA_CONG_ENTRY_DATA_SIZE) {
		log_report("invalid SL specified\n");
		free(new);
		return -1;
	}

	*sl = sltmp;
	*val_offset = (unsigned int)(val_str - new);

	free(new);
	return 0;
}