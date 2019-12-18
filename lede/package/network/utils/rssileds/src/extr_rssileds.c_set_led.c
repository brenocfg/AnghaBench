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
struct led {unsigned char state; int /*<<< orphan*/  controlfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned char) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int set_led(struct led *led, unsigned char value)
{
	char buf[8];

	if ( ! led )
		return -1;

	if ( ! led->controlfd )
		return -1;

	if ( led->state == value )
		return 0;

	snprintf(buf, 8, "%d", value);

	rewind(led->controlfd);

	if ( ! fwrite(buf, sizeof(char), strlen(buf), led->controlfd) )
		return -2;

	fflush(led->controlfd);
	led->state=value;

	return 0;
}