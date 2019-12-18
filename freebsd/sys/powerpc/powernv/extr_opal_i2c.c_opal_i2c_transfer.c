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
typedef  int uint32_t ;
struct opal_i2c_softc {int /*<<< orphan*/  opal_id; } ;
struct opal_i2c_request {int /*<<< orphan*/  buffer_pa; int /*<<< orphan*/  size; int /*<<< orphan*/  addr; int /*<<< orphan*/  type; } ;
struct iic_msg {int flags; int slave; scalar_t__ buf; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_LOCK (struct opal_i2c_softc*) ; 
 int /*<<< orphan*/  I2C_UNLOCK (struct opal_i2c_softc*) ; 
 int IIC_M_RD ; 
 int /*<<< orphan*/  OPAL_I2C_RAW_READ ; 
 int /*<<< orphan*/  OPAL_I2C_RAW_WRITE ; 
 struct opal_i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htobe16 (int) ; 
 int /*<<< orphan*/  htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htobe64 (int /*<<< orphan*/ ) ; 
 int i2c_opal_send_request (int /*<<< orphan*/ ,struct opal_i2c_request*) ; 
 int /*<<< orphan*/  memset (struct opal_i2c_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_kextract (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
opal_i2c_transfer(device_t dev, struct iic_msg *msgs, uint32_t nmsgs)
{
	struct opal_i2c_softc *sc;
	int i, err = 0;
	struct opal_i2c_request req;

	sc = device_get_softc(dev);

	memset(&req, 0, sizeof(req));

	I2C_LOCK(sc);
	for (i = 0; i < nmsgs; i++) {
		req.type = (msgs[i].flags & IIC_M_RD) ?
		    OPAL_I2C_RAW_READ : OPAL_I2C_RAW_WRITE;
		req.addr = htobe16(msgs[i].slave >> 1);
		req.size = htobe32(msgs[i].len);
		req.buffer_pa = htobe64(pmap_kextract((uint64_t)msgs[i].buf));

		err = i2c_opal_send_request(sc->opal_id, &req);
	}
	I2C_UNLOCK(sc);

	return (err);
}