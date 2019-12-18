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
typedef  int uint8_t ;
struct cqspi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_READ_STATUS ; 
 int STATUS_WIP ; 
 int cqspi_cmd_read (struct cqspi_softc*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
cqspi_wait_ready(struct cqspi_softc *sc)
{
	uint8_t data;
	int ret;

	do {
		ret = cqspi_cmd_read(sc, CMD_READ_STATUS, &data, 1);
	} while (data & STATUS_WIP);

	return (0);
}