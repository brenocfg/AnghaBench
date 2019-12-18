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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct rbcfg_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_u32 (void*) ; 
 int rbcfg_find_tag (struct rbcfg_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static int
rbcfg_get_u32(struct rbcfg_ctx *ctx, uint16_t id, uint32_t *val)
{
	void *tag_data;
	uint16_t tag_len;
	int err;

	err = rbcfg_find_tag(ctx, id, &tag_len, &tag_data);
	if (err)
		return err;

	*val = get_u32(tag_data);
	return 0;
}