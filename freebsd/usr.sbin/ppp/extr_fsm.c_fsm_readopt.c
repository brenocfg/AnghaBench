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
typedef  int /*<<< orphan*/  u_char ;
struct fsm_opt_hdr {int dummy; } ;
struct TYPE_2__ {int len; } ;
struct fsm_opt {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int,...) ; 

struct fsm_opt *
fsm_readopt(u_char **cp)
{
  struct fsm_opt *o = (struct fsm_opt *)*cp;

  if (o->hdr.len < sizeof(struct fsm_opt_hdr)) {
    log_Printf(LogERROR, "Bad option length %d (out of phase?)\n", o->hdr.len);
    return NULL;
  }

  *cp += o->hdr.len;

  if (o->hdr.len > sizeof(struct fsm_opt)) {
    log_Printf(LogERROR, "Warning: Truncating option length from %d to %d\n",
               o->hdr.len, (int)sizeof(struct fsm_opt));
    o->hdr.len = sizeof(struct fsm_opt);
  }

  return o;
}