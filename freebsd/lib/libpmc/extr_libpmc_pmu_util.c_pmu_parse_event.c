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
struct pmu_event_desc {int ped_umask; void* ped_l3_slice; void* ped_l3_thread; void* ped_config1; void* ped_ch_mask; void* ped_fc_mask; void* ped_ldlat; void* ped_frontend; void* ped_edge; void* ped_inv; void* ped_cmask; void* ped_any; void* ped_offcore_rsp; void* ped_period; void* ped_event; } ;

/* Variables and functions */
 void* DEFAULT_SAMPLE_COUNT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bzero (struct pmu_event_desc*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char const*) ; 
 char* strsep (char**,char*) ; 
 void* strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
pmu_parse_event(struct pmu_event_desc *ped, const char *eventin)
{
	char *event;
	char *kvp, *key, *value, *r;
	char *debug;

	if ((event = strdup(eventin)) == NULL)
		return (ENOMEM);
	r = event;
	bzero(ped, sizeof(*ped));
	ped->ped_period = DEFAULT_SAMPLE_COUNT;
	ped->ped_umask = -1;
	while ((kvp = strsep(&event, ",")) != NULL) {
		key = strsep(&kvp, "=");
		if (key == NULL)
			abort();
		value = kvp;
		if (strcmp(key, "umask") == 0)
			ped->ped_umask = strtol(value, NULL, 16);
		else if (strcmp(key, "event") == 0)
			ped->ped_event = strtol(value, NULL, 16);
		else if (strcmp(key, "period") == 0)
			ped->ped_period = strtol(value, NULL, 10);
		else if (strcmp(key, "offcore_rsp") == 0)
			ped->ped_offcore_rsp = strtol(value, NULL, 16);
		else if (strcmp(key, "any") == 0)
			ped->ped_any = strtol(value, NULL, 10);
		else if (strcmp(key, "cmask") == 0)
			ped->ped_cmask = strtol(value, NULL, 10);
		else if (strcmp(key, "inv") == 0)
			ped->ped_inv = strtol(value, NULL, 10);
		else if (strcmp(key, "edge") == 0)
			ped->ped_edge = strtol(value, NULL, 10);
		else if (strcmp(key, "frontend") == 0)
			ped->ped_frontend = strtol(value, NULL, 16);
		else if (strcmp(key, "ldlat") == 0)
			ped->ped_ldlat = strtol(value, NULL, 16);
		else if (strcmp(key, "fc_mask") == 0)
			ped->ped_fc_mask = strtol(value, NULL, 16);
		else if (strcmp(key, "ch_mask") == 0)
			ped->ped_ch_mask = strtol(value, NULL, 16);
		else if (strcmp(key, "config1") == 0)
			ped->ped_config1 = strtol(value, NULL, 16);
		else if (strcmp(key, "l3_thread_mask") == 0)
			ped->ped_l3_thread = strtol(value, NULL, 16);
		else if (strcmp(key, "l3_slice_mask") == 0)
			ped->ped_l3_slice = strtol(value, NULL, 16);
		else {
			debug = getenv("PMUDEBUG");
			if (debug != NULL && strcmp(debug, "true") == 0 && value != NULL)
				printf("unrecognized kvpair: %s:%s\n", key, value);
		}
	}
	free(r);
	return (0);
}