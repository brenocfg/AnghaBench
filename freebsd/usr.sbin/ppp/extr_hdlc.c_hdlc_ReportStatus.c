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
struct TYPE_4__ {int /*<<< orphan*/  unknownproto; int /*<<< orphan*/  badcommand; int /*<<< orphan*/  badaddr; int /*<<< orphan*/  badfcs; } ;
struct hdlc {TYPE_1__ stats; } ;
struct cmdargs {int /*<<< orphan*/  prompt; TYPE_3__* cx; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; TYPE_2__* physical; } ;
struct TYPE_5__ {struct hdlc hdlc; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDLC_ADDR ; 
 int /*<<< orphan*/  HDLC_UI ; 
 int /*<<< orphan*/  prompt_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

int
hdlc_ReportStatus(struct cmdargs const *arg)
{
  struct hdlc *hdlc = &arg->cx->physical->hdlc;

  prompt_Printf(arg->prompt, "%s HDLC level errors:\n", arg->cx->name);
  prompt_Printf(arg->prompt, " Bad Frame Check Sequence fields: %u\n",
	        hdlc->stats.badfcs);
  prompt_Printf(arg->prompt, " Bad address (!= 0x%02x) fields:    %u\n",
	        HDLC_ADDR, hdlc->stats.badaddr);
  prompt_Printf(arg->prompt, " Bad command (!= 0x%02x) fields:    %u\n",
	        HDLC_UI, hdlc->stats.badcommand);
  prompt_Printf(arg->prompt, " Unrecognised protocol fields:    %u\n",
	        hdlc->stats.unknownproto);
  return 0;
}