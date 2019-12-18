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
typedef  int /*<<< orphan*/  zap_name_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZAP_NEED_CD ; 
 int fzap_add_cd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int fzap_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
fzap_add(zap_name_t *zn,
    uint64_t integer_size, uint64_t num_integers,
    const void *val, void *tag, dmu_tx_t *tx)
{
	int err = fzap_check(zn, integer_size, num_integers);
	if (err != 0)
		return (err);

	return (fzap_add_cd(zn, integer_size, num_integers,
	    val, ZAP_NEED_CD, tag, tx));
}