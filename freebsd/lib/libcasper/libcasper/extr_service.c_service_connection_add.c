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
struct service_connection {int /*<<< orphan*/  sc_magic; int /*<<< orphan*/ * sc_chan; int /*<<< orphan*/ * sc_limits; } ;
struct service {scalar_t__ s_magic; int /*<<< orphan*/  s_connections; } ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  SERVICE_CONNECTION_MAGIC ; 
 scalar_t__ SERVICE_MAGIC ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct service_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cap_unwrap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cap_wrap (int,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct service_connection*) ; 
 struct service_connection* malloc (int) ; 
 int /*<<< orphan*/ * nvlist_clone (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sc_next ; 
 int /*<<< orphan*/  service_get_channel_flags (struct service*) ; 

struct service_connection *
service_connection_add(struct service *service, int sock,
    const nvlist_t *limits)
{
	struct service_connection *sconn;
	int serrno;

	assert(service->s_magic == SERVICE_MAGIC);

	sconn = malloc(sizeof(*sconn));
	if (sconn == NULL)
		return (NULL);
	sconn->sc_chan = cap_wrap(sock,
	    service_get_channel_flags(service));
	if (sconn->sc_chan == NULL) {
		serrno = errno;
		free(sconn);
		errno = serrno;
		return (NULL);
	}
	if (limits == NULL) {
		sconn->sc_limits = NULL;
	} else {
		sconn->sc_limits = nvlist_clone(limits);
		if (sconn->sc_limits == NULL) {
			serrno = errno;
			(void)cap_unwrap(sconn->sc_chan, NULL);
			free(sconn);
			errno = serrno;
			return (NULL);
		}
	}
	sconn->sc_magic = SERVICE_CONNECTION_MAGIC;
	TAILQ_INSERT_TAIL(&service->s_connections, sconn, sc_next);
	return (sconn);
}