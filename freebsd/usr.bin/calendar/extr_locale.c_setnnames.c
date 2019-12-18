#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tm {int tm_wday; int tm_mon; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {void* len; int /*<<< orphan*/ * name; } ;
struct TYPE_7__ {void* len; int /*<<< orphan*/ * name; } ;
struct TYPE_6__ {void* len; int /*<<< orphan*/ * name; } ;
struct TYPE_5__ {void* len; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 TYPE_4__* fndays ; 
 TYPE_3__* fnmonths ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* ndays ; 
 TYPE_1__* nmonths ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 void* strlen (char*) ; 

void
setnnames(void)
{
	char buf[80];
	int i, l;
	struct tm tm;

	memset(&tm, 0, sizeof(struct tm));
	for (i = 0; i < 7; i++) {
		tm.tm_wday = i;
		strftime(buf, sizeof(buf), "%a", &tm);
		for (l = strlen(buf);
		     l > 0 && isspace((unsigned char)buf[l - 1]);
		     l--)
			;
		buf[l] = '\0';
		if (ndays[i].name != NULL)
			free(ndays[i].name);
		if ((ndays[i].name = strdup(buf)) == NULL)
			errx(1, "cannot allocate memory");
		ndays[i].len = strlen(buf);

		strftime(buf, sizeof(buf), "%A", &tm);
		for (l = strlen(buf);
		     l > 0 && isspace((unsigned char)buf[l - 1]);
		     l--)
			;
		buf[l] = '\0';
		if (fndays[i].name != NULL)
			free(fndays[i].name);
		if ((fndays[i].name = strdup(buf)) == NULL)
			errx(1, "cannot allocate memory");
		fndays[i].len = strlen(buf);
	}

	memset(&tm, 0, sizeof(struct tm));
	for (i = 0; i < 12; i++) {
		tm.tm_mon = i;
		strftime(buf, sizeof(buf), "%b", &tm);
		for (l = strlen(buf);
		     l > 0 && isspace((unsigned char)buf[l - 1]);
		     l--)
			;
		buf[l] = '\0';
		if (nmonths[i].name != NULL)
			free(nmonths[i].name);
		if ((nmonths[i].name = strdup(buf)) == NULL)
			errx(1, "cannot allocate memory");
		nmonths[i].len = strlen(buf);

		strftime(buf, sizeof(buf), "%B", &tm);
		for (l = strlen(buf);
		     l > 0 && isspace((unsigned char)buf[l - 1]);
		     l--)
			;
		buf[l] = '\0';
		if (fnmonths[i].name != NULL)
			free(fnmonths[i].name);
		if ((fnmonths[i].name = strdup(buf)) == NULL)
			errx(1, "cannot allocate memory");
		fnmonths[i].len = strlen(buf);
	}
}