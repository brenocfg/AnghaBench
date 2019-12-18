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
struct client {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct client** clients ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 size_t num_clients ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct client *
get_client(const char *slave)
{
    size_t i;
    for (i = 0; i < num_clients; i++)
	if (strcmp(slave, clients[i]->name) == 0)
	    return clients[i];
    errx(1, "failed to find client %s", slave);
}