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
typedef  int /*<<< orphan*/  uint16_t ;
struct dmar_unit {int dummy; } ;
struct dmar_ctx {int dummy; } ;

/* Variables and functions */
 struct dmar_ctx* dmar_get_ctx_for_dev1 (struct dmar_unit*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,void const*,int,int,int) ; 

struct dmar_ctx *
dmar_get_ctx_for_devpath(struct dmar_unit *dmar, uint16_t rid,
    int dev_domain, int dev_busno,
    const void *dev_path, int dev_path_len,
    bool id_mapped, bool rmrr_init)
{

	return (dmar_get_ctx_for_dev1(dmar, NULL, rid, dev_domain, dev_busno,
	    dev_path, dev_path_len, id_mapped, rmrr_init));
}