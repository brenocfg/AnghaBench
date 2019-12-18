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
typedef  scalar_t__ u64 ;
struct sfe_ipv4_debug_xml_write_state {size_t iter_exception; int /*<<< orphan*/  state; } ;
struct sfe_ipv4 {int /*<<< orphan*/  lock; scalar_t__* exception_events64; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAR_DEV_MSG_SIZE ; 
 size_t SFE_IPV4_EXCEPTION_EVENT_LAST ; 
 scalar_t__ copy_to_user (char*,char*,int /*<<< orphan*/ ) ; 
 char** sfe_ipv4_exception_events_string ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool sfe_ipv4_debug_dev_read_exceptions_exception(struct sfe_ipv4 *si, char *buffer, char *msg, size_t *length,
							 int *total_read, struct sfe_ipv4_debug_xml_write_state *ws)
{
	u64 ct;

	spin_lock_bh(&si->lock);
	ct = si->exception_events64[ws->iter_exception];
	spin_unlock_bh(&si->lock);

	if (ct) {
		int bytes_read;

		bytes_read = snprintf(msg, CHAR_DEV_MSG_SIZE,
				      "\t\t<exception name=\"%s\" count=\"%llu\" />\n",
				      sfe_ipv4_exception_events_string[ws->iter_exception],
				      ct);
		if (copy_to_user(buffer + *total_read, msg, CHAR_DEV_MSG_SIZE)) {
			return false;
		}

		*length -= bytes_read;
		*total_read += bytes_read;
	}

	ws->iter_exception++;
	if (ws->iter_exception >= SFE_IPV4_EXCEPTION_EVENT_LAST) {
		ws->iter_exception = 0;
		ws->state++;
	}

	return true;
}