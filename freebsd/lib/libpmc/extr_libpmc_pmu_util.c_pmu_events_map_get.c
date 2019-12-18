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
struct pmu_events_map {char* cpuid; } ;
struct TYPE_3__ {size_t rm_eo; size_t rm_so; } ;
typedef  TYPE_1__ regmatch_t ;
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int /*<<< orphan*/  REG_EXTENDED ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 struct pmu_events_map* pmu_events_map ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int regexec (int /*<<< orphan*/ *,char*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 size_t strlen (char*) ; 
 int sysctlbyname (char*,char*,size_t*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct pmu_events_map *
pmu_events_map_get(const char *cpuid)
{
	regex_t re;
	regmatch_t pmatch[1];
	size_t s, len;
	char buf[64];
	int match;
	const struct pmu_events_map *pme;

	if (cpuid != NULL) {
		memcpy(buf, cpuid, 64);
	} else {
		if (sysctlbyname("kern.hwpmc.cpuid", (void *)NULL, &s,
		    (void *)NULL, 0) == -1)
			return (NULL);
		if (sysctlbyname("kern.hwpmc.cpuid", buf, &s,
		    (void *)NULL, 0) == -1)
			return (NULL);
	}
	for (pme = pmu_events_map; pme->cpuid != NULL; pme++) {
		if (regcomp(&re, pme->cpuid, REG_EXTENDED) != 0) {
			printf("regex '%s' failed to compile, ignoring\n",
			    pme->cpuid);
			continue;
		}
		match = regexec(&re, buf, 1, pmatch, 0);
		regfree(&re);
		if (match == 0) {
			len = pmatch[0].rm_eo - pmatch[0].rm_so;
			if(len == strlen(buf))
				return (pme);
		}
	}
	return (NULL);
}