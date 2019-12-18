#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_6__ {scalar_t__ width; int cum; int cog; int loc; int matched; } ;
typedef  TYPE_1__ fg_pspan ;

/* Variables and functions */
 scalar_t__ FG_PSPAN_MAX_WIDTH ; 
 int FG_PSPAN_MIN_CUM_PRESSURE ; 
 int FG_SCALE_FACTOR ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fg_detect_pspans(int *p, u_int num_sensors,
    u_int      max_spans, /* max # of pspans permitted */
    fg_pspan  *spans,     /* finger spans */
    u_int     *nspans_p)  /* num spans detected */
{
	u_int i;
	int   maxp;             /* max pressure seen within a span */
	u_int num_spans = 0;

	enum fg_pspan_state {
		ATP_PSPAN_INACTIVE,
		ATP_PSPAN_INCREASING,
		ATP_PSPAN_DECREASING,
	} state; /* state of the pressure span */

	/*
	 * The following is a simple state machine to track
	 * the phase of the pressure span.
	 */
	memset(spans, 0, max_spans * sizeof(fg_pspan));
	maxp = 0;
	state = ATP_PSPAN_INACTIVE;
	for (i = 0; i < num_sensors; i++) {
		if (num_spans >= max_spans)
			break;

		if (p[i] == 0) {
			if (state == ATP_PSPAN_INACTIVE) {
				/*
				 * There is no pressure information for this
				 * sensor, and we aren't tracking a finger.
				 */
				continue;
			} else {
				state = ATP_PSPAN_INACTIVE;
				maxp = 0;
				num_spans++;
			}
		} else {
			switch (state) {
			case ATP_PSPAN_INACTIVE:
				state = ATP_PSPAN_INCREASING;
				maxp  = p[i];
				break;

			case ATP_PSPAN_INCREASING:
				if (p[i] > maxp)
					maxp = p[i];
				else if (p[i] <= (maxp >> 1))
					state = ATP_PSPAN_DECREASING;
				break;

			case ATP_PSPAN_DECREASING:
				if (p[i] > p[i - 1]) {
					/*
					 * This is the beginning of
					 * another span; change state
					 * to give the appearance that
					 * we're starting from an
					 * inactive span, and then
					 * re-process this reading in
					 * the next iteration.
					 */
					num_spans++;
					state = ATP_PSPAN_INACTIVE;
					maxp  = 0;
					i--;
					continue;
				}
				break;
			}

			/* Update the finger span with this reading. */
			spans[num_spans].width++;
			spans[num_spans].cum += p[i];
			spans[num_spans].cog += p[i] * (i + 1);
		}
	}
	if (state != ATP_PSPAN_INACTIVE)
		num_spans++;    /* close the last finger span */

	/* post-process the spans */
	for (i = 0; i < num_spans; i++) {
		/* filter away unwanted pressure spans */
		if ((spans[i].cum < FG_PSPAN_MIN_CUM_PRESSURE) ||
		    (spans[i].width > FG_PSPAN_MAX_WIDTH)) {
			if ((i + 1) < num_spans) {
				memcpy(&spans[i], &spans[i + 1],
				    (num_spans - i - 1) * sizeof(fg_pspan));
				i--;
			}
			num_spans--;
			continue;
		}

		/* compute this span's representative location */
		spans[i].loc = spans[i].cog * FG_SCALE_FACTOR /
			spans[i].cum;

		spans[i].matched = false; /* not yet matched against a stroke */
	}

	*nspans_p = num_spans;
}