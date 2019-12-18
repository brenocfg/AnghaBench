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
struct led {struct led* sysfspath; int /*<<< orphan*/  controlfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct led*) ; 

void close_led(struct led **led)
{
	fclose((*led)->controlfd);
	free((*led)->sysfspath);
	free((*led));
	(*led)=NULL;
}