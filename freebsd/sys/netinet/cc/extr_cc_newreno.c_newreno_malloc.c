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
struct newreno {int /*<<< orphan*/  beta_ecn; int /*<<< orphan*/  beta; } ;
struct cc_var {struct newreno* cc_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NEWRENO ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  V_newreno_beta ; 
 int /*<<< orphan*/  V_newreno_beta_ecn ; 
 struct newreno* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct newreno *
newreno_malloc(struct cc_var *ccv)
{
	struct newreno *nreno;

	nreno = malloc(sizeof(struct newreno), M_NEWRENO, M_NOWAIT);
	if (nreno != NULL) {
		/* NB: nreno is not zeroed, so initialise all fields. */
		nreno->beta = V_newreno_beta;
		nreno->beta_ecn = V_newreno_beta_ecn;
		ccv->cc_data = nreno;
	}

	return (nreno);
}