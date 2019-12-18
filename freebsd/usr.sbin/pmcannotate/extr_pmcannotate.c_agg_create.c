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
typedef  int /*<<< orphan*/  u_int ;
struct aggent {uintptr_t ag_ostart; uintptr_t ag_oend; int /*<<< orphan*/  ag_nsamples; int /*<<< orphan*/ * ag_name; } ;

/* Variables and functions */
 struct aggent* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct aggent*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static struct aggent *
agg_create(const char *name, u_int nsamples, uintptr_t start, uintptr_t end)
{
	struct aggent *agg;

	agg = calloc(1, sizeof(struct aggent));
	if (agg == NULL)
		return (NULL);
	agg->ag_name = strdup(name);
	if (agg->ag_name == NULL) {
		free(agg);
		return (NULL);
	}
	agg->ag_nsamples = nsamples;
	agg->ag_ostart = start;
	agg->ag_oend = end;
	return (agg);
}