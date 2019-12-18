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
struct uni_funcs {int dummy; } ;
struct uni {int /*<<< orphan*/  timer399; int /*<<< orphan*/  timer398; int /*<<< orphan*/  timer397; int /*<<< orphan*/  init322; int /*<<< orphan*/  timer322; int /*<<< orphan*/  timer317; int /*<<< orphan*/  timer316; int /*<<< orphan*/  init316; int /*<<< orphan*/  timer313; int /*<<< orphan*/  timer310; int /*<<< orphan*/  timer308; int /*<<< orphan*/  init308; int /*<<< orphan*/  timer303; int /*<<< orphan*/  init303; int /*<<< orphan*/  timer301; int /*<<< orphan*/  cx; int /*<<< orphan*/  calls; int /*<<< orphan*/  timer309; int /*<<< orphan*/  delq; int /*<<< orphan*/  workq; scalar_t__ sb_tb; int /*<<< orphan*/  proto; void* arg; struct uni_funcs const* funcs; } ;

/* Variables and functions */
 struct uni* INS_ALLOC () ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIMER_INIT_UNI (struct uni*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIPROTO_UNI40U ; 
 int /*<<< orphan*/  UNI_T301_DEFAULT ; 
 int /*<<< orphan*/  UNI_T303_CNT_DEFAULT ; 
 int /*<<< orphan*/  UNI_T303_DEFAULT ; 
 int /*<<< orphan*/  UNI_T308_CNT_DEFAULT ; 
 int /*<<< orphan*/  UNI_T308_DEFAULT ; 
 int /*<<< orphan*/  UNI_T309_DEFAULT ; 
 int /*<<< orphan*/  UNI_T310U_DEFAULT ; 
 int /*<<< orphan*/  UNI_T313_DEFAULT ; 
 int /*<<< orphan*/  UNI_T316_CNT_DEFAULT ; 
 int /*<<< orphan*/  UNI_T316_DEFAULT ; 
 int /*<<< orphan*/  UNI_T317_DEFAULT ; 
 int /*<<< orphan*/  UNI_T322_CNT_DEFAULT ; 
 int /*<<< orphan*/  UNI_T322_DEFAULT ; 
 int /*<<< orphan*/  UNI_T397_DEFAULT ; 
 int /*<<< orphan*/  UNI_T398_DEFAULT ; 
 int /*<<< orphan*/  UNI_T399U_DEFAULT ; 
 int /*<<< orphan*/  t309 ; 
 int /*<<< orphan*/  t316 ; 
 int /*<<< orphan*/  t317 ; 
 int /*<<< orphan*/  uni_init (struct uni*) ; 
 int /*<<< orphan*/  uni_initcx (int /*<<< orphan*/ *) ; 

struct uni *
uni_create(void *arg, const struct uni_funcs *funcs)
{
	struct uni *uni;

	if ((uni = INS_ALLOC()) == NULL)
		return (NULL);

	uni_init(uni);

	uni->funcs = funcs;
	uni->arg = arg;
	uni->proto = UNIPROTO_UNI40U;
	uni->sb_tb = 0;
	TAILQ_INIT(&uni->workq);
	TAILQ_INIT(&uni->delq);
	TIMER_INIT_UNI(uni, t309);
	uni->timer309 = UNI_T309_DEFAULT;
	TAILQ_INIT(&uni->calls);
	uni_initcx(&uni->cx);
	TIMER_INIT_UNI(uni, t317);
	TIMER_INIT_UNI(uni, t316);

	uni->timer301 = UNI_T301_DEFAULT;
	uni->init303 = UNI_T303_CNT_DEFAULT;
	uni->timer303 = UNI_T303_DEFAULT;
	uni->init308 = UNI_T308_CNT_DEFAULT;
	uni->timer308 = UNI_T308_DEFAULT;
	uni->timer310 = UNI_T310U_DEFAULT;
	uni->timer313 = UNI_T313_DEFAULT;
	uni->init316 = UNI_T316_CNT_DEFAULT;
	uni->timer316 = UNI_T316_DEFAULT;
	uni->timer317 = UNI_T317_DEFAULT;
	uni->timer322 = UNI_T322_DEFAULT;
	uni->init322 = UNI_T322_CNT_DEFAULT;
	uni->timer397 = UNI_T397_DEFAULT;
	uni->timer398 = UNI_T398_DEFAULT;
	uni->timer399 = UNI_T399U_DEFAULT;

	return (uni);
}