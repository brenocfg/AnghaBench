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
struct host1x_softc {int /*<<< orphan*/  clients; } ;
struct client_info {scalar_t__ activated; int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (struct host1x_softc*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct client_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK (struct host1x_softc*) ; 
 struct host1x_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_e ; 
 struct client_info* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
host1x_register_client(device_t dev, device_t client)
{
	struct host1x_softc *sc;
	struct client_info *entry;

	sc = device_get_softc(dev);

	entry = malloc(sizeof(struct client_info), M_DEVBUF, M_WAITOK | M_ZERO);
	entry->client = client;
	entry->activated = 0;

	LOCK(sc);
	TAILQ_INSERT_TAIL(&sc->clients, entry, list_e);
	UNLOCK(sc);

	return (0);
}