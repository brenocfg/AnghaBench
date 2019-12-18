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
 int CHATDEBUG_SEND ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 unsigned char PAUSE_CH ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  alarm (int /*<<< orphan*/ ) ; 
 scalar_t__ alarmed ; 
 int /*<<< orphan*/  chat_alarm ; 
 int chat_debug ; 
 int /*<<< orphan*/  chat_unalarm () ; 
 int /*<<< orphan*/  cleanstr (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  result (int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int write (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int
chat_send(char const *str)
{
	int r = 0;

	if (chat_debug & CHATDEBUG_SEND)
		syslog(LOG_DEBUG, "chat_send '%s'", cleanstr(str, strlen(str)));

	if (*str) {
                alarm(chat_alarm);
                alarmed = 0;
                while (r == 0 && *str)
                {
                        unsigned char ch = (unsigned char)*str++;

                        if (alarmed)
        			r = 3;
                        else if (ch == PAUSE_CH)
				usleep(500000); /* 1/2 second */
			else  {
				usleep(10000);	/* be kind to modem */
                                if (write(STDOUT_FILENO, &ch, 1) != 1)
        		  		r = alarmed ? 3 : 2;
                        }
                }
                alarm(0);
                chat_unalarm();
                alarmed = 0;
	}

        if (chat_debug & CHATDEBUG_SEND)
          syslog(LOG_DEBUG, "chat_send %s", result(r));

        return r;
}