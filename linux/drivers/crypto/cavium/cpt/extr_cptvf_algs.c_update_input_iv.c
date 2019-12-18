#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct TYPE_4__ {int /*<<< orphan*/  dlen; } ;
struct cpt_request_info {TYPE_2__ req; TYPE_1__* in; } ;
struct TYPE_3__ {size_t size; void* vptr; } ;

/* Variables and functions */

__attribute__((used)) static inline void update_input_iv(struct cpt_request_info *req_info,
				   u8 *iv, u32 enc_iv_len,
				   u32 *argcnt)
{
	/* Setting the iv information */
	req_info->in[*argcnt].vptr = (void *)iv;
	req_info->in[*argcnt].size = enc_iv_len;
	req_info->req.dlen += enc_iv_len;

	++(*argcnt);
}