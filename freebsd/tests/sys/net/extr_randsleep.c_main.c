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
typedef  scalar_t__ useconds_t ;

/* Variables and functions */
 scalar_t__ RANDOM_MAX ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ random () ; 
 int /*<<< orphan*/  srandomdev () ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep (scalar_t__) ; 

int main(int argc, char** argv){
	useconds_t max_usecs, usecs;
	double frac;

	if (argc != 2) {
		printf("Usage: randsleep <max_microseconds>\n");
		exit(2);
	}

	errno = 0;
	max_usecs = (useconds_t)strtol(argv[1], NULL, 0);
	if (errno != 0) {
		perror("strtol");
		exit(1);
	}
	srandomdev();
	frac = (double)random() / (double)RANDOM_MAX;
	usecs = (useconds_t)((double)max_usecs * frac);
	usleep(usecs);

	return (0);
}