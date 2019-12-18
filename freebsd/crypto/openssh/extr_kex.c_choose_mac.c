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
struct sshmac {char* name; scalar_t__ enabled; int /*<<< orphan*/ * key; } ;
struct ssh {int dummy; } ;

/* Variables and functions */
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_NO_MAC_ALG_MATCH ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ mac_setup (struct sshmac*,char*) ; 
 char* match_list (char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
choose_mac(struct ssh *ssh, struct sshmac *mac, char *client, char *server)
{
	char *name = match_list(client, server, NULL);

	if (name == NULL)
		return SSH_ERR_NO_MAC_ALG_MATCH;
	if (mac_setup(mac, name) < 0) {
		free(name);
		return SSH_ERR_INTERNAL_ERROR;
	}
	mac->name = name;
	mac->key = NULL;
	mac->enabled = 0;
	return 0;
}