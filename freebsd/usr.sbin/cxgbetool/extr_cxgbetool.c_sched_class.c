#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int level; int mode; int rateunit; int ratemode; int channel; int cl; int minrate; int maxrate; int weight; int pktsize; } ;
struct TYPE_4__ {int minmax; } ;
struct TYPE_5__ {TYPE_3__ params; TYPE_1__ config; } ;
struct t4_sched_params {int subcmd; int type; TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  op ;
typedef  void* int8_t ;
typedef  void* int32_t ;
typedef  void* int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_T4_SCHED_CLASS ; 
 int EINVAL ; 
 int SCHED_CLASS_LEVEL_CH_RL ; 
 int SCHED_CLASS_LEVEL_CL_RL ; 
 int SCHED_CLASS_LEVEL_CL_WRR ; 
 int SCHED_CLASS_MODE_CLASS ; 
 int SCHED_CLASS_MODE_FLOW ; 
 int SCHED_CLASS_RATEMODE_ABS ; 
 int SCHED_CLASS_RATEMODE_REL ; 
 int SCHED_CLASS_RATEUNIT_BITS ; 
 int SCHED_CLASS_RATEUNIT_PKTS ; 
 int SCHED_CLASS_SUBCMD_CONFIG ; 
 int SCHED_CLASS_SUBCMD_PARAMS ; 
 int SCHED_CLASS_TYPE_PACKET ; 
 int doit (int /*<<< orphan*/ ,struct t4_sched_params*) ; 
 int /*<<< orphan*/  get_sched_param (char*,char const**,long*) ; 
 int /*<<< orphan*/  in_range (int,int,int) ; 
 int /*<<< orphan*/  memset (struct t4_sched_params*,int,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
sched_class(int argc, const char *argv[])
{
	struct t4_sched_params op;
	int errs, i;

	memset(&op, 0xff, sizeof(op));
	op.subcmd = -1;
	op.type = -1;
	if (argc == 0) {
		warnx("missing scheduling sub-command");
		return (EINVAL);
	}
	if (!strcmp(argv[0], "config")) {
		op.subcmd = SCHED_CLASS_SUBCMD_CONFIG;
		op.u.config.minmax = -1;
	} else if (!strcmp(argv[0], "params")) {
		op.subcmd = SCHED_CLASS_SUBCMD_PARAMS;
		op.u.params.level = op.u.params.mode = op.u.params.rateunit =
		    op.u.params.ratemode = op.u.params.channel =
		    op.u.params.cl = op.u.params.minrate = op.u.params.maxrate =
		    op.u.params.weight = op.u.params.pktsize = -1;
	} else {
		warnx("invalid scheduling sub-command \"%s\"", argv[0]);
		return (EINVAL);
	}

	/* Decode remaining arguments ... */
	errs = 0;
	for (i = 1; i < argc; i += 2) {
		const char **args = &argv[i];
		long l;

		if (i + 1 == argc) {
			warnx("missing argument for \"%s\"", args[0]);
			errs++;
			break;
		}

		if (!strcmp(args[0], "type")) {
			if (!strcmp(args[1], "packet"))
				op.type = SCHED_CLASS_TYPE_PACKET;
			else {
				warnx("invalid type parameter \"%s\"", args[1]);
				errs++;
			}

			continue;
		}

		if (op.subcmd == SCHED_CLASS_SUBCMD_CONFIG) {
			if(!get_sched_param("minmax", args, &l))
				op.u.config.minmax = (int8_t)l;
			else {
				warnx("unknown scheduler config parameter "
				    "\"%s\"", args[0]);
				errs++;
			}

			continue;
		}

		/* Rest applies only to SUBCMD_PARAMS */
		if (op.subcmd != SCHED_CLASS_SUBCMD_PARAMS)
			continue;

		if (!strcmp(args[0], "level")) {
			if (!strcmp(args[1], "cl-rl"))
				op.u.params.level = SCHED_CLASS_LEVEL_CL_RL;
			else if (!strcmp(args[1], "cl-wrr"))
				op.u.params.level = SCHED_CLASS_LEVEL_CL_WRR;
			else if (!strcmp(args[1], "ch-rl"))
				op.u.params.level = SCHED_CLASS_LEVEL_CH_RL;
			else {
				warnx("invalid level parameter \"%s\"",
				    args[1]);
				errs++;
			}
		} else if (!strcmp(args[0], "mode")) {
			if (!strcmp(args[1], "class"))
				op.u.params.mode = SCHED_CLASS_MODE_CLASS;
			else if (!strcmp(args[1], "flow"))
				op.u.params.mode = SCHED_CLASS_MODE_FLOW;
			else {
				warnx("invalid mode parameter \"%s\"", args[1]);
				errs++;
			}
		} else if (!strcmp(args[0], "rate-unit")) {
			if (!strcmp(args[1], "bits"))
				op.u.params.rateunit = SCHED_CLASS_RATEUNIT_BITS;
			else if (!strcmp(args[1], "pkts"))
				op.u.params.rateunit = SCHED_CLASS_RATEUNIT_PKTS;
			else {
				warnx("invalid rate-unit parameter \"%s\"",
				    args[1]);
				errs++;
			}
		} else if (!strcmp(args[0], "rate-mode")) {
			if (!strcmp(args[1], "relative"))
				op.u.params.ratemode = SCHED_CLASS_RATEMODE_REL;
			else if (!strcmp(args[1], "absolute"))
				op.u.params.ratemode = SCHED_CLASS_RATEMODE_ABS;
			else {
				warnx("invalid rate-mode parameter \"%s\"",
				    args[1]);
				errs++;
			}
		} else if (!get_sched_param("channel", args, &l))
			op.u.params.channel = (int8_t)l;
		else if (!get_sched_param("class", args, &l))
			op.u.params.cl = (int8_t)l;
		else if (!get_sched_param("min-rate", args, &l))
			op.u.params.minrate = (int32_t)l;
		else if (!get_sched_param("max-rate", args, &l))
			op.u.params.maxrate = (int32_t)l;
		else if (!get_sched_param("weight", args, &l))
			op.u.params.weight = (int16_t)l;
		else if (!get_sched_param("pkt-size", args, &l))
			op.u.params.pktsize = (int16_t)l;
		else {
			warnx("unknown scheduler parameter \"%s\"", args[0]);
			errs++;
		}
	}

	/*
	 * Catch some logical fallacies in terms of argument combinations here
	 * so we can offer more than just the EINVAL return from the driver.
	 * The driver will be able to catch a lot more issues since it knows
	 * the specifics of the device hardware capabilities like how many
	 * channels, classes, etc. the device supports.
	 */
	if (op.type < 0) {
		warnx("sched \"type\" parameter missing");
		errs++;
	}
	if (op.subcmd == SCHED_CLASS_SUBCMD_CONFIG) {
		if (op.u.config.minmax < 0) {
			warnx("sched config \"minmax\" parameter missing");
			errs++;
		}
	}
	if (op.subcmd == SCHED_CLASS_SUBCMD_PARAMS) {
		if (op.u.params.level < 0) {
			warnx("sched params \"level\" parameter missing");
			errs++;
		}
		if (op.u.params.mode < 0 &&
		    op.u.params.level == SCHED_CLASS_LEVEL_CL_RL) {
			warnx("sched params \"mode\" parameter missing");
			errs++;
		}
		if (op.u.params.rateunit < 0 &&
		    (op.u.params.level == SCHED_CLASS_LEVEL_CL_RL ||
		    op.u.params.level == SCHED_CLASS_LEVEL_CH_RL)) {
			warnx("sched params \"rate-unit\" parameter missing");
			errs++;
		}
		if (op.u.params.ratemode < 0 &&
		    (op.u.params.level == SCHED_CLASS_LEVEL_CL_RL ||
		    op.u.params.level == SCHED_CLASS_LEVEL_CH_RL)) {
			warnx("sched params \"rate-mode\" parameter missing");
			errs++;
		}
		if (op.u.params.channel < 0) {
			warnx("sched params \"channel\" missing");
			errs++;
		}
		if (op.u.params.cl < 0 &&
		    (op.u.params.level == SCHED_CLASS_LEVEL_CL_RL ||
		    op.u.params.level == SCHED_CLASS_LEVEL_CL_WRR)) {
			warnx("sched params \"class\" missing");
			errs++;
		}
		if (op.u.params.maxrate < 0 &&
		    (op.u.params.level == SCHED_CLASS_LEVEL_CL_RL ||
		    op.u.params.level == SCHED_CLASS_LEVEL_CH_RL)) {
			warnx("sched params \"max-rate\" missing for "
			    "rate-limit level");
			errs++;
		}
		if (op.u.params.level == SCHED_CLASS_LEVEL_CL_WRR &&
		    (op.u.params.weight < 1 || op.u.params.weight > 99)) {
			warnx("sched params \"weight\" missing or invalid "
			    "(not 1-99) for weighted-round-robin level");
			errs++;
		}
		if (op.u.params.pktsize < 0 &&
		    op.u.params.level == SCHED_CLASS_LEVEL_CL_RL) {
			warnx("sched params \"pkt-size\" missing for "
			    "rate-limit level");
			errs++;
		}
		if (op.u.params.mode == SCHED_CLASS_MODE_FLOW &&
		    op.u.params.ratemode != SCHED_CLASS_RATEMODE_ABS) {
			warnx("sched params mode flow needs rate-mode absolute");
			errs++;
		}
		if (op.u.params.ratemode == SCHED_CLASS_RATEMODE_REL &&
		    !in_range(op.u.params.maxrate, 1, 100)) {
                        warnx("sched params \"max-rate\" takes "
			    "percentage value(1-100) for rate-mode relative");
                        errs++;
                }
                if (op.u.params.ratemode == SCHED_CLASS_RATEMODE_ABS &&
		    !in_range(op.u.params.maxrate, 1, 100000000)) {
                        warnx("sched params \"max-rate\" takes "
			    "value(1-100000000) for rate-mode absolute");
                        errs++;
                }
                if (op.u.params.maxrate > 0 &&
		    op.u.params.maxrate < op.u.params.minrate) {
                        warnx("sched params \"max-rate\" is less than "
			    "\"min-rate\"");
                        errs++;
                }
	}

	if (errs > 0) {
		warnx("%d error%s in sched-class command", errs,
		    errs == 1 ? "" : "s");
		return (EINVAL);
	}

	return doit(CHELSIO_T4_SCHED_CLASS, &op);
}