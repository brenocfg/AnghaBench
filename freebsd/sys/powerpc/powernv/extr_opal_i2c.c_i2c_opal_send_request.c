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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct opal_msg {int dummy; } ;
struct opal_i2c_request {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int OPAL_ASYNC_COMPLETION ; 
 int /*<<< orphan*/  OPAL_I2C_REQUEST ; 
 int OPAL_SUCCESS ; 
 int /*<<< orphan*/  memset (struct opal_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opal_alloc_async_token () ; 
 int opal_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opal_free_async_token (int /*<<< orphan*/ ) ; 
 int opal_get_async_rc (struct opal_msg) ; 
 int opal_wait_completion (struct opal_msg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtophys (struct opal_i2c_request*) ; 

__attribute__((used)) static int
i2c_opal_send_request(uint32_t bus_id, struct opal_i2c_request *req)
{
	struct opal_msg msg;
	uint64_t token;
	int rc;

	token = opal_alloc_async_token();

	memset(&msg, 0, sizeof(msg));

	rc = opal_call(OPAL_I2C_REQUEST, token, bus_id,
	    vtophys(req));
	if (rc != OPAL_ASYNC_COMPLETION)
		goto out;

	rc = opal_wait_completion(&msg, sizeof(msg), token);

	if (rc != OPAL_SUCCESS)
		goto out;

	rc = opal_get_async_rc(msg);

out:
	opal_free_async_token(token);

	return (rc);
}