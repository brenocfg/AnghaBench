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
struct uni_config {int /*<<< orphan*/  timer399; int /*<<< orphan*/  timer398; int /*<<< orphan*/  timer397; int /*<<< orphan*/  init322; int /*<<< orphan*/  timer322; int /*<<< orphan*/  timer317; int /*<<< orphan*/  init316; int /*<<< orphan*/  timer316; int /*<<< orphan*/  timer313; int /*<<< orphan*/  timer310; int /*<<< orphan*/  timer309; int /*<<< orphan*/  init308; int /*<<< orphan*/  timer308; int /*<<< orphan*/  init303; int /*<<< orphan*/  timer303; int /*<<< orphan*/  timer301; int /*<<< orphan*/  popt; int /*<<< orphan*/  option; int /*<<< orphan*/  proto; } ;
struct TYPE_2__ {scalar_t__ cause_hard; scalar_t__ bearer_hard; scalar_t__ git_hard; scalar_t__ q2932; } ;
struct uni {int /*<<< orphan*/  timer399; int /*<<< orphan*/  timer398; int /*<<< orphan*/  timer397; int /*<<< orphan*/  init322; int /*<<< orphan*/  timer322; int /*<<< orphan*/  timer317; int /*<<< orphan*/  init316; int /*<<< orphan*/  timer316; int /*<<< orphan*/  timer313; int /*<<< orphan*/  timer310; int /*<<< orphan*/  timer309; int /*<<< orphan*/  init308; int /*<<< orphan*/  timer308; int /*<<< orphan*/  init303; int /*<<< orphan*/  timer303; int /*<<< orphan*/  timer301; scalar_t__ sb_tb; TYPE_1__ cx; int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNIOPT_BEARER_HARD ; 
 int /*<<< orphan*/  UNIOPT_CAUSE_HARD ; 
 int /*<<< orphan*/  UNIOPT_GIT_HARD ; 
 int /*<<< orphan*/  UNIPROTO_GFP ; 
 int /*<<< orphan*/  UNIPROTO_SB_TB ; 

void
uni_get_config(const struct uni *uni, struct uni_config *config)
{
	config->proto = uni->proto;

	config->popt = 0;
	if (uni->cx.q2932)
		config->popt |= UNIPROTO_GFP;

	config->option = 0;
	if (uni->cx.git_hard)
		config->option |= UNIOPT_GIT_HARD;
	if (uni->cx.bearer_hard)
		config->option |= UNIOPT_BEARER_HARD;
	if (uni->cx.cause_hard)
		config->option |= UNIOPT_CAUSE_HARD;
	if (uni->sb_tb)
		config->popt |= UNIPROTO_SB_TB;

	config->timer301 = uni->timer301;
	config->timer303 = uni->timer303;
	config->init303 = uni->init303;
	config->timer308 = uni->timer308;
	config->init308 = uni->init308;
	config->timer309 = uni->timer309;
	config->timer310 = uni->timer310;
	config->timer313 = uni->timer313;
	config->timer316 = uni->timer316;
	config->init316 = uni->init316;
	config->timer317 = uni->timer317;
	config->timer322 = uni->timer322;
	config->init322 = uni->init322;
	config->timer397 = uni->timer397;
	config->timer398 = uni->timer398;
	config->timer399 = uni->timer399;
}