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
typedef  scalar_t__ uint16_t ;
struct cma_device {int /*<<< orphan*/  verbs; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int ibv_query_pkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 

__attribute__((used)) static int ucma_find_pkey(struct cma_device *cma_dev, uint8_t port_num,
			  __be16 pkey, uint16_t *pkey_index)
{
	int ret, i;
	__be16 chk_pkey;

	for (i = 0, ret = 0; !ret; i++) {
		ret = ibv_query_pkey(cma_dev->verbs, port_num, i, &chk_pkey);
		if (!ret && pkey == chk_pkey) {
			*pkey_index = (uint16_t) i;
			return 0;
		}
	}
	return ERR(EINVAL);
}