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
typedef  int /*<<< orphan*/  tmp ;
struct gpiobus_ivar {int npins; int* pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 

__attribute__((used)) static void
gpiobus_print_pins(struct gpiobus_ivar *devi, char *buf, size_t buflen)
{
	char tmp[128];
	int i, range_start, range_stop, need_coma;

	if (devi->npins == 0)
		return;

	need_coma = 0;
	range_start = range_stop = devi->pins[0];
	for (i = 1; i < devi->npins; i++) {
		if (devi->pins[i] != (range_stop + 1)) {
			if (need_coma)
				strlcat(buf, ",", buflen);
			memset(tmp, 0, sizeof(tmp));
			if (range_start != range_stop)
				snprintf(tmp, sizeof(tmp) - 1, "%d-%d",
				    range_start, range_stop);
			else
				snprintf(tmp, sizeof(tmp) - 1, "%d",
				    range_start);
			strlcat(buf, tmp, buflen);

			range_start = range_stop = devi->pins[i];
			need_coma = 1;
		}
		else
			range_stop++;
	}

	if (need_coma)
		strlcat(buf, ",", buflen);
	memset(tmp, 0, sizeof(tmp));
	if (range_start != range_stop)
		snprintf(tmp, sizeof(tmp) - 1, "%d-%d",
		    range_start, range_stop);
	else
		snprintf(tmp, sizeof(tmp) - 1, "%d",
		    range_start);
	strlcat(buf, tmp, buflen);
}