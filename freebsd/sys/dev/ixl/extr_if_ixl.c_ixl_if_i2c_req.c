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
struct ixl_pf {scalar_t__ (* read_i2c_byte ) (struct ixl_pf*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct ifi2creq {int len; int /*<<< orphan*/ * data; int /*<<< orphan*/  dev_addr; scalar_t__ offset; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 struct ixl_pf* iflib_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct ixl_pf*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ixl_if_i2c_req(if_ctx_t ctx, struct ifi2creq *req)
{
	struct ixl_pf		*pf = iflib_get_softc(ctx);

	if (pf->read_i2c_byte == NULL)
		return (EINVAL);

	for (int i = 0; i < req->len; i++)
		if (pf->read_i2c_byte(pf, req->offset + i,
		    req->dev_addr, &req->data[i]))
			return (EIO);
	return (0);
}