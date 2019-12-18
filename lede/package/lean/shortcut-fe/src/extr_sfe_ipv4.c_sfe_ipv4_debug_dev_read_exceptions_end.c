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
struct sfe_ipv4_debug_xml_write_state {int /*<<< orphan*/  state; } ;
struct sfe_ipv4 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAR_DEV_MSG_SIZE ; 
 scalar_t__ copy_to_user (char*,char*,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool sfe_ipv4_debug_dev_read_exceptions_end(struct sfe_ipv4 *si, char *buffer, char *msg, size_t *length,
						   int *total_read, struct sfe_ipv4_debug_xml_write_state *ws)
{
	int bytes_read;

	bytes_read = snprintf(msg, CHAR_DEV_MSG_SIZE, "\t</exceptions>\n");
	if (copy_to_user(buffer + *total_read, msg, CHAR_DEV_MSG_SIZE)) {
		return false;
	}

	*length -= bytes_read;
	*total_read += bytes_read;

	ws->state++;
	return true;
}