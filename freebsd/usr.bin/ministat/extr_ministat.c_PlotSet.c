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
struct plot {scalar_t__ span; char** bar; int width; int x0; int dx; int height; char* data; int /*<<< orphan*/  num_datasets; scalar_t__ separate_bars; } ;
struct dataset {unsigned int n; int* points; } ;

/* Variables and functions */
 int Avg (struct dataset*) ; 
 int Median (struct dataset*) ; 
 int Stddev (struct dataset*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char** calloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isnan (int) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 struct plot plot ; 
 char* realloc (char*,int) ; 

__attribute__((used)) static void
PlotSet(struct dataset *ds, int val)
{
	struct plot *pl;
	int i, j, m, x;
	unsigned n;
	int bar;

	pl = &plot;
	if (pl->span == 0)
		return;

	if (pl->separate_bars)
		bar = val-1;
	else
		bar = 0;

	if (pl->bar == NULL) {
		pl->bar = calloc(sizeof(char *), pl->num_datasets);
		assert(pl->bar != NULL);
	}

	if (pl->bar[bar] == NULL) {
		pl->bar[bar] = malloc(pl->width);
		assert(pl->bar[bar] != NULL);
		memset(pl->bar[bar], 0, pl->width);
	}

	m = 1;
	i = -1;
	j = 0;
	for (n = 0; n < ds->n; n++) {
		x = (ds->points[n] - pl->x0) / pl->dx;
		if (x == i) {
			j++;
			if (j > m)
				m = j;
		} else {
			j = 1;
			i = x;
		}
	}
	m += 1;
	if (m > pl->height) {
		pl->data = realloc(pl->data, pl->width * m);
		assert(pl->data != NULL);
		memset(pl->data + pl->height * pl->width, 0,
		    (m - pl->height) * pl->width);
	}
	pl->height = m;
	i = -1;
	for (n = 0; n < ds->n; n++) {
		x = (ds->points[n] - pl->x0) / pl->dx;
		if (x == i) {
			j++;
		} else {
			j = 1;
			i = x;
		}
		pl->data[j * pl->width + x] |= val;
	}
	if (!isnan(Stddev(ds))) {
		x = ((Avg(ds) - Stddev(ds)) - pl->x0) / pl->dx;
		m = ((Avg(ds) + Stddev(ds)) - pl->x0) / pl->dx;
		pl->bar[bar][m] = '|';
		pl->bar[bar][x] = '|';
		for (i = x + 1; i < m; i++)
			if (pl->bar[bar][i] == 0)
				pl->bar[bar][i] = '_';
	}
	x = (Median(ds) - pl->x0) / pl->dx;
	pl->bar[bar][x] = 'M';
	x = (Avg(ds) - pl->x0) / pl->dx;
	pl->bar[bar][x] = 'A';
}