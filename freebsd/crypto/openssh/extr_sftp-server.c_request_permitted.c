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
struct sftp_handler {int /*<<< orphan*/  name; scalar_t__ does_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug2 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* match_list (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ readonly ; 
 int /*<<< orphan*/ * request_blacklist ; 
 int /*<<< orphan*/ * request_whitelist ; 
 int /*<<< orphan*/  verbose (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
request_permitted(struct sftp_handler *h)
{
	char *result;

	if (readonly && h->does_write) {
		verbose("Refusing %s request in read-only mode", h->name);
		return 0;
	}
	if (request_blacklist != NULL &&
	    ((result = match_list(h->name, request_blacklist, NULL))) != NULL) {
		free(result);
		verbose("Refusing blacklisted %s request", h->name);
		return 0;
	}
	if (request_whitelist != NULL &&
	    ((result = match_list(h->name, request_whitelist, NULL))) != NULL) {
		free(result);
		debug2("Permitting whitelisted %s request", h->name);
		return 1;
	}
	if (request_whitelist != NULL) {
		verbose("Refusing non-whitelisted %s request", h->name);
		return 0;
	}
	return 1;
}