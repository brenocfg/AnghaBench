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
typedef  int /*<<< orphan*/  uint8_t ;
struct smt_entry {int dummy; } ;
struct smt_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 struct smt_entry* t4_find_or_alloc_sme (struct smt_data*,int /*<<< orphan*/ *) ; 

struct smt_entry *
t4_smt_alloc_switching(struct smt_data *s, uint8_t *smac)
{
	struct smt_entry *e;

	MPASS(s != NULL);
	rw_wlock(&s->lock);
	e = t4_find_or_alloc_sme(s, smac);
	rw_wunlock(&s->lock);
	return e;
}