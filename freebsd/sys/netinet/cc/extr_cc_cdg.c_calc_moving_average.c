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
struct qdiff_sample {long qdiff; } ;
struct cdg {long num_samples; long sample_q_size; int /*<<< orphan*/  qdiffmax_q; scalar_t__ max_qtrend; int /*<<< orphan*/  qdiffmin_q; scalar_t__ min_qtrend; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 struct qdiff_sample* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct qdiff_sample*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdiff_lnk ; 
 int /*<<< orphan*/  qdiffsample_zone ; 
 struct qdiff_sample* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
calc_moving_average(struct cdg *cdg_data, long qdiff_max, long qdiff_min)
{
	struct qdiff_sample *qds;

	++cdg_data->num_samples;
	if (cdg_data->num_samples > cdg_data->sample_q_size) {
		/* Minimum RTT. */
		qds = STAILQ_FIRST(&cdg_data->qdiffmin_q);
		cdg_data->min_qtrend =  cdg_data->min_qtrend +
		    (qdiff_min - qds->qdiff) / cdg_data->sample_q_size;
		STAILQ_REMOVE_HEAD(&cdg_data->qdiffmin_q, qdiff_lnk);
		qds->qdiff = qdiff_min;
		STAILQ_INSERT_TAIL(&cdg_data->qdiffmin_q, qds, qdiff_lnk);

		/* Maximum RTT. */
		qds = STAILQ_FIRST(&cdg_data->qdiffmax_q);
		cdg_data->max_qtrend =  cdg_data->max_qtrend +
		    (qdiff_max - qds->qdiff) / cdg_data->sample_q_size;
		STAILQ_REMOVE_HEAD(&cdg_data->qdiffmax_q, qdiff_lnk);
		qds->qdiff = qdiff_max;
		STAILQ_INSERT_TAIL(&cdg_data->qdiffmax_q, qds, qdiff_lnk);
		--cdg_data->num_samples;
	} else {
		qds = uma_zalloc(qdiffsample_zone, M_NOWAIT);
		if (qds != NULL) {
			cdg_data->min_qtrend = cdg_data->min_qtrend +
			    qdiff_min / cdg_data->sample_q_size;
			qds->qdiff = qdiff_min;
			STAILQ_INSERT_TAIL(&cdg_data->qdiffmin_q, qds,
			    qdiff_lnk);
		}

		qds = uma_zalloc(qdiffsample_zone, M_NOWAIT);
		if (qds) {
			cdg_data->max_qtrend = cdg_data->max_qtrend +
			    qdiff_max / cdg_data->sample_q_size;
			qds->qdiff = qdiff_max;
			STAILQ_INSERT_TAIL(&cdg_data->qdiffmax_q, qds,
			    qdiff_lnk);
		}
	}
}