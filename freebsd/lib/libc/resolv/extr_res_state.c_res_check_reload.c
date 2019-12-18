#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct timespec {scalar_t__ tv_sec; } ;
struct TYPE_10__ {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct stat {TYPE_3__ st_mtim; } ;
struct TYPE_11__ {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct __res_state_ext {scalar_t__ reload_period; scalar_t__ conf_stat; TYPE_4__ conf_mtim; } ;
typedef  TYPE_5__* res_state ;
struct TYPE_8__ {struct __res_state_ext* ext; } ;
struct TYPE_9__ {TYPE_1__ _ext; } ;
struct TYPE_12__ {int options; TYPE_2__ _u; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC_FAST ; 
 int RES_INIT ; 
 int /*<<< orphan*/  _PATH_RESCONF ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static res_state
res_check_reload(res_state statp)
{
	struct timespec now;
	struct stat sb;
	struct __res_state_ext *ext;

	if ((statp->options & RES_INIT) == 0) {
		return (statp);
	}

	ext = statp->_u._ext.ext;
	if (ext == NULL || ext->reload_period == 0) {
		return (statp);
	}

	if (clock_gettime(CLOCK_MONOTONIC_FAST, &now) != 0 ||
	    (now.tv_sec - ext->conf_stat) < ext->reload_period) {
		return (statp);
	}

	ext->conf_stat = now.tv_sec;
	if (stat(_PATH_RESCONF, &sb) == 0 &&
	    (sb.st_mtim.tv_sec  != ext->conf_mtim.tv_sec ||
	     sb.st_mtim.tv_nsec != ext->conf_mtim.tv_nsec)) {
		statp->options &= ~RES_INIT;
	}

	return (statp);
}