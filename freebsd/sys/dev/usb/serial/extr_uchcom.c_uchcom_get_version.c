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
struct uchcom_softc {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int UCHCOM_INPUT_BUF_SIZE ; 
 int /*<<< orphan*/  UCHCOM_REQ_GET_VERSION ; 
 int /*<<< orphan*/  uchcom_ctrl_read (struct uchcom_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
uchcom_get_version(struct uchcom_softc *sc, uint8_t *rver)
{
	uint8_t buf[UCHCOM_INPUT_BUF_SIZE];

	uchcom_ctrl_read(sc, UCHCOM_REQ_GET_VERSION, 0, 0, buf, sizeof(buf));

	if (rver)
		*rver = buf[0];
}