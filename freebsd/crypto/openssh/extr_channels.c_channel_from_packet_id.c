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
struct ssh {int dummy; } ;
typedef  int /*<<< orphan*/  Channel ;

/* Variables and functions */
 int /*<<< orphan*/ * channel_lookup (struct ssh*,int) ; 
 int channel_parse_id (struct ssh*,char const*,char const*) ; 
 int /*<<< orphan*/  ssh_packet_disconnect (struct ssh*,char*,char const*,int) ; 

__attribute__((used)) static Channel *
channel_from_packet_id(struct ssh *ssh, const char *where, const char *what)
{
	int id = channel_parse_id(ssh, where, what);
	Channel *c;

	if ((c = channel_lookup(ssh, id)) == NULL) {
		ssh_packet_disconnect(ssh,
		    "%s packet referred to nonexistent channel %d", what, id);
	}
	return c;
}