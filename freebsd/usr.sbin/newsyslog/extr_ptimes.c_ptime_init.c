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
struct ptime_data {int /*<<< orphan*/  did_adj4dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  TNYET_ADJ4DST ; 
 struct ptime_data* malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct ptime_data*,struct ptime_data const*,int) ; 
 int /*<<< orphan*/  memset (struct ptime_data*,char,int) ; 

struct ptime_data *
ptime_init(const struct ptime_data *optsrc)
{
	struct ptime_data *newdata;

	newdata = malloc(sizeof(struct ptime_data));
	if (optsrc != NULL) {
		memcpy(newdata, optsrc, sizeof(struct ptime_data));
	} else {
		memset(newdata, '\0', sizeof(struct ptime_data));
		newdata->did_adj4dst = TNYET_ADJ4DST;
	}

	return (newdata);
}