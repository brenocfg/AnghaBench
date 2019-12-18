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
struct pqisrc_softstate {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ERR (char*,int) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  PQISRC_SHUTDOWN ; 
 int PQI_STATUS_SUCCESS ; 
 int pqisrc_flush_cache (struct pqisrc_softstate*,int /*<<< orphan*/ ) ; 

int
smartpqi_shutdown(void *arg)
{
	struct pqisrc_softstate *softs = NULL;
	int rval = 0;

	DBG_FUNC("IN\n");

	softs = (struct pqisrc_softstate *)arg;

	rval = pqisrc_flush_cache(softs, PQISRC_SHUTDOWN);
	if (rval != PQI_STATUS_SUCCESS) {
		DBG_ERR("Unable to flush adapter cache! rval = %d", rval);
	}

	DBG_FUNC("OUT\n");
		
	return rval;
}