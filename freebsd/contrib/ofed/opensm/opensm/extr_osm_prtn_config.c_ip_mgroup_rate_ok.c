#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  rate; } ;
struct TYPE_7__ {int /*<<< orphan*/  raw; } ;
struct precreate_mgroup {TYPE_4__ flags; TYPE_3__ mgid; } ;
struct TYPE_6__ {int /*<<< orphan*/  rate; } ;
struct part_conf {TYPE_2__ flags; TYPE_1__* p_prtn; int /*<<< orphan*/  p_log; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/  pkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  FALSE ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cl_ntoh16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static inline boolean_t ip_mgroup_rate_ok(struct part_conf *conf,
				struct precreate_mgroup *group)
{
	char gid_str[INET6_ADDRSTRLEN];

	if (group->flags.rate == conf->flags.rate)
		return (TRUE);

	OSM_LOG(conf->p_log, OSM_LOG_ERROR,
		"IP MC group (%s) specified with invalid rate (%d): "
		"partition pkey = 0x%04x (%s) "
		"[Partition broadcast group rate = %d]\n",
		inet_ntop(AF_INET6, group->mgid.raw, gid_str, sizeof gid_str),
		group->flags.rate, cl_ntoh16(conf->p_prtn->pkey),
		conf->p_prtn->name, conf->flags.rate);
	return (FALSE);
}