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
struct opal_sensor_softc {int dummy; } ;
struct opal_msg {int /*<<< orphan*/ * params; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EIO ; 
 int OPAL_ASYNC_COMPLETION ; 
 int /*<<< orphan*/  OPAL_SENSOR_READ ; 
 int OPAL_SUCCESS ; 
 int /*<<< orphan*/  SENSOR_LOCK (struct opal_sensor_softc*) ; 
 int /*<<< orphan*/  SENSOR_UNLOCK (struct opal_sensor_softc*) ; 
 int /*<<< orphan*/  bzero (struct opal_msg*,int) ; 
 int opal_alloc_async_token () ; 
 int opal_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opal_free_async_token (int) ; 
 int opal_wait_completion (struct opal_msg*,int,int) ; 
 int /*<<< orphan*/  vtophys (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
opal_sensor_get_val(struct opal_sensor_softc *sc, uint32_t key, uint64_t *val)
{
	struct opal_msg msg;
	uint32_t val32;
	int rv, token;

	token = opal_alloc_async_token();
	SENSOR_LOCK(sc);
	rv = opal_call(OPAL_SENSOR_READ, key, token, vtophys(&val32));

	if (rv == OPAL_ASYNC_COMPLETION) {
		/* Sleep a little to let things settle. */
		DELAY(100);
		bzero(&msg, sizeof(msg));
		rv = opal_wait_completion(&msg, sizeof(msg), token);

		if (rv == OPAL_SUCCESS)
			val32 = msg.params[0];
	}
	SENSOR_UNLOCK(sc);

	if (rv == OPAL_SUCCESS)
		*val = val32;
	else
		rv = EIO;
	
	opal_free_async_token(token);
	return (rv);
}