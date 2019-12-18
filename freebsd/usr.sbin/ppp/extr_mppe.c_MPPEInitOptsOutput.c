#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct TYPE_2__ {int len; } ;
struct fsm_opt {int /*<<< orphan*/  data; TYPE_1__ hdr; } ;
struct ccp_config {int dummy; } ;
struct bundle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogCCP ; 
 scalar_t__ MPPE_ConfigVal (struct bundle*,struct ccp_config const*) ; 
 int /*<<< orphan*/  MPPE_MasterKeyValid ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ua_htonl (scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
MPPEInitOptsOutput(struct bundle *bundle, struct fsm_opt *o,
                   const struct ccp_config *cfg)
{
  u_int32_t mval;

  o->hdr.len = 6;

  if (!MPPE_MasterKeyValid) {
    log_Printf(LogCCP, "MPPE: MasterKey is invalid,"
               " MPPE is available only with CHAP81 authentication\n");
    mval = 0;
    ua_htonl(&mval, o->data);
    return;
  }


  mval = MPPE_ConfigVal(bundle, cfg);
  ua_htonl(&mval, o->data);
}