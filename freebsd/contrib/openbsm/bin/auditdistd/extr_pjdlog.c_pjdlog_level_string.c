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

/* Variables and functions */
#define  LOG_ALERT 135 
#define  LOG_CRIT 134 
#define  LOG_DEBUG 133 
#define  LOG_EMERG 132 
#define  LOG_ERR 131 
#define  LOG_INFO 130 
#define  LOG_NOTICE 129 
#define  LOG_WARNING 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static const char *
pjdlog_level_string(int loglevel)
{

	switch (loglevel) {
	case LOG_EMERG:
		return ("EMERG");
	case LOG_ALERT:
		return ("ALERT");
	case LOG_CRIT:
		return ("CRIT");
	case LOG_ERR:
		return ("ERROR");
	case LOG_WARNING:
		return ("WARNING");
	case LOG_NOTICE:
		return ("NOTICE");
	case LOG_INFO:
		return ("INFO");
	case LOG_DEBUG:
		return ("DEBUG");
	}
	assert(!"Invalid log level.");
	abort();	/* XXX: gcc */
}