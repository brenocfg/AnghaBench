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
struct videomode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  print_xf86_mode (struct videomode*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  vesagtf_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct videomode*) ; 

int
main (int argc, char *argv[])
{
	struct videomode m;

	if (argc != 4) {
		printf("usage: %s x y refresh\n", argv[0]);
		exit(1);
	}
    
	vesagtf_mode(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), &m);

        print_xf86_mode(&m);
    
	return 0;
    
}