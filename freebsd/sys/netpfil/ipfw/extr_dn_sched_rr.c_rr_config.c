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
struct rr_schk {int min_q; int max_q; int q_bytes; } ;
struct dn_schk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND (char*) ; 

__attribute__((used)) static int
rr_config(struct dn_schk *_schk)
{
	struct rr_schk *schk = (struct rr_schk *)(_schk + 1);
	ND("called");

	/* use reasonable quantums (64..2k bytes, default 1500) */
	schk->min_q = 64;
	schk->max_q = 2048;
	schk->q_bytes = 1500;	/* quantum */

	return 0;
}