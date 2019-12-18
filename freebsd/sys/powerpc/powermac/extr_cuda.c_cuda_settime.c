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
typedef  scalar_t__ uint32_t ;
struct timespec {scalar_t__ tv_sec; } ;
struct cuda_softc {int /*<<< orphan*/  sc_mutex; } ;
typedef  int /*<<< orphan*/  sec ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_WRITE_RTC ; 
 int /*<<< orphan*/  CUDA_PSEUDO ; 
 scalar_t__ DIFF19041970 ; 
 int /*<<< orphan*/  cuda_send (struct cuda_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct cuda_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cuda_settime(device_t dev, struct timespec *ts)
{
	struct cuda_softc *sc = device_get_softc(dev);
	uint8_t cmd[] = {CUDA_PSEUDO, CMD_WRITE_RTC, 0, 0, 0, 0};
	uint32_t sec;

	sec = ts->tv_sec + DIFF19041970;
	memcpy(&cmd[2], &sec, sizeof(sec));

	mtx_lock(&sc->sc_mutex);
	cuda_send(sc, 0, 6, cmd);
	mtx_unlock(&sc->sc_mutex);

	return (0);
}