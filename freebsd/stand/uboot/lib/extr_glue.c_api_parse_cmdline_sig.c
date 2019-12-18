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
struct api_signature {int dummy; } ;

/* Variables and functions */
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ opterr ; 
 int optind ; 
 int optreset ; 
 unsigned long strtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ valid_sig (struct api_signature*) ; 

int
api_parse_cmdline_sig(int argc, char **argv, struct api_signature **sig)
{
	unsigned long api_address;
	int c;

	api_address = 0;
	opterr = 0;
	optreset = 1;
	optind = 1;

	while ((c = getopt (argc, argv, "a:")) != -1)
		switch (c) {
		case 'a':
			api_address = strtoul(optarg, NULL, 16);
			break;
		default:
			break;
		}

	if (api_address != 0) {
		*sig = (struct api_signature *)api_address;
		if (valid_sig(*sig))
			return (1);
	}

	return (0);
}