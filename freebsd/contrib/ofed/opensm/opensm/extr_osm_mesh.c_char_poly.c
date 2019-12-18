#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  osm_log_t ;
struct TYPE_8__ {TYPE_1__* p_osm; } ;
typedef  TYPE_2__ lash_t ;
struct TYPE_7__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSM_LOG_EXIT (int /*<<< orphan*/ *) ; 
 scalar_t__ determinant (TYPE_2__*,int,int,int***,int*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int*** pm_alloc (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  pm_free (int***,int) ; 
 int* poly_alloc (TYPE_2__*,int) ; 

__attribute__((used)) static int char_poly(lash_t *p_lash, int rank, int **matrix, int **poly)
{
	osm_log_t *p_log = &p_lash->p_osm->log;
	int ret = -1;
	int i, j;
	int ***m = NULL;
	int *p = NULL;
	int deg = rank;

	OSM_LOG_ENTER(p_log);

	do {
		if (!matrix)
			break;

		if (!(p = poly_alloc(p_lash, deg)))
			break;

		if (!(m = pm_alloc(p_lash, rank, deg))) {
			free(p);
			p = NULL;
			break;
		}

		for (i = 0; i < rank; i++) {
			for (j = 0; j < rank; j++) {
				m[i][j][0] = matrix[i][j];
			}
			m[i][i][1] = -1;
		}

		if (determinant(p_lash, deg, rank, m, p)) {
			free(p);
			p = NULL;
			break;
		}

		ret = 0;
	} while (0);

	pm_free(m, rank);
	*poly = p;

	OSM_LOG_EXIT(p_log);
	return ret;
}