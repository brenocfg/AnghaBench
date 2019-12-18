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
 int CHATDEBUG_EXPECT ; 
 int CHATDEBUG_RECEIVE ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  alarm (int /*<<< orphan*/ ) ; 
 scalar_t__ alarmed ; 
 int /*<<< orphan*/  chat_alarm ; 
 int chat_debug ; 
 int /*<<< orphan*/  chat_unalarm () ; 
 int /*<<< orphan*/  cleanchr (int /*<<< orphan*/ *,unsigned char) ; 
 int /*<<< orphan*/  cleanstr (char const*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 scalar_t__ memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int read (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  result (int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
chat_expect(const char *str)
{
	int len, r = 0;

	if (chat_debug & CHATDEBUG_EXPECT)
		syslog(LOG_DEBUG, "chat_expect '%s'", cleanstr(str, strlen(str)));

	if ((len = strlen(str)) > 0) {
		int i = 0;
		char * got;

		if ((got = malloc(len + 1)) == NULL)
			r = 1;
		else {

			memset(got, 0, len+1);
			alarm(chat_alarm);
			alarmed = 0;

			while (r == 0 && i < len) {
				if (alarmed)
					r = 3;
				else {
					unsigned char ch;

					if (read(STDIN_FILENO, &ch, 1) == 1) {

						if (chat_debug & CHATDEBUG_RECEIVE)
							syslog(LOG_DEBUG, "chat_recv '%s' m=%d",
								cleanchr(NULL, ch), i);

						if (ch == str[i])
							got[i++] = ch;
						else if (i > 0) {
							int j = 1;

							/* See if we can resync on a
							 * partial match in our buffer
							 */
							while (j < i && memcmp(got + j, str, i - j) != 0)
								j++;
							if (j < i)
								memcpy(got, got + j, i - j);
							i -= j;
						}
					} else
						r = alarmed ? 3 : 2;
				}
			}
			alarm(0);
        		chat_unalarm();
        		alarmed = 0;
        		free(got);
		}
	}

	if (chat_debug & CHATDEBUG_EXPECT)
		syslog(LOG_DEBUG, "chat_expect %s", result(r));

	return r;
}