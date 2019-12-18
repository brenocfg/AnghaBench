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
struct ioc_play_msf {int start_m; int start_s; int start_f; int end_m; int end_s; int end_f; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDIOCPLAYMSF ; 
 int /*<<< orphan*/  fd ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
play_msf(int start_m, int start_s, int start_f,
	int end_m, int end_s, int end_f)
{
	struct ioc_play_msf a;

	a.start_m = start_m;
	a.start_s = start_s;
	a.start_f = start_f;
	a.end_m = end_m;
	a.end_s = end_s;
	a.end_f = end_f;

	return ioctl (fd, CDIOCPLAYMSF, (char *) &a);
}