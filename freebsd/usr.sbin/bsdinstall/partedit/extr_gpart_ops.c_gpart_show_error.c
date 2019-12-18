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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dialog_msgbox (char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*,...) ; 
 char* strerror (int) ; 
 int strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gpart_show_error(const char *title, const char *explanation, const char *errstr)
{
	char *errmsg;
	char message[512];
	int error;

	if (explanation == NULL)
		explanation = "";

	error = strtol(errstr, &errmsg, 0);
	if (errmsg != errstr) {
		while (errmsg[0] == ' ')
			errmsg++;
		if (errmsg[0] != '\0')
			sprintf(message, "%s%s. %s", explanation,
			    strerror(error), errmsg);
		else
			sprintf(message, "%s%s", explanation, strerror(error));
	} else {
		sprintf(message, "%s%s", explanation, errmsg);
	}

	dialog_msgbox(title, message, 0, 0, TRUE);
}