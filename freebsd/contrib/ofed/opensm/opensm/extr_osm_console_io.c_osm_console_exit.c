#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  osm_log_t ;
struct TYPE_4__ {int socket; } ;
typedef  TYPE_1__ osm_console_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OSM_LOG_INFO ; 
 int /*<<< orphan*/  cio_close (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 

void osm_console_exit(osm_console_t * p_oct, osm_log_t * p_log)
{
#ifdef ENABLE_OSM_CONSOLE_LOOPBACK
	cio_close(p_oct, p_log);
	if (p_oct->socket > 0) {
		OSM_LOG(p_log, OSM_LOG_INFO, "Closing console socket\n");
		close(p_oct->socket);
		p_oct->socket = -1;
	}
#endif
}