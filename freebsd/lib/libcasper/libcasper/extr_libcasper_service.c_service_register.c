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
struct casper_service {int /*<<< orphan*/ * cs_service; } ;
typedef  int /*<<< orphan*/  service_limit_func_t ;
typedef  int /*<<< orphan*/  service_command_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct casper_service*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  casper_services ; 
 int /*<<< orphan*/  cs_next ; 
 int /*<<< orphan*/  free (struct casper_service*) ; 
 struct casper_service* malloc (int) ; 
 int /*<<< orphan*/ * service_alloc (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * service_find (char const*) ; 

struct casper_service *
service_register(const char *name, service_limit_func_t *limitfunc,
   service_command_func_t *commandfunc, uint64_t flags)
{
	struct casper_service *casserv;

	if (commandfunc == NULL)
		return (NULL);
	if (name == NULL || name[0] == '\0')
		return (NULL);
	if (service_find(name) != NULL)
		return (NULL);

	casserv = malloc(sizeof(*casserv));
	if (casserv == NULL)
		return (NULL);

	casserv->cs_service = service_alloc(name, limitfunc, commandfunc,
	    flags);
	if (casserv->cs_service == NULL) {
		free(casserv);
		return (NULL);
	}
	TAILQ_INSERT_TAIL(&casper_services, casserv, cs_next);

	return (casserv);
}