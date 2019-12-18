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
struct option {char* name; int has_arg; char val; } ;
struct ibv_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt_long (int,char**,char*,struct option*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibv_free_device_list (struct ibv_device**) ; 
 struct ibv_device** ibv_get_device_list (int*) ; 
 char* ibv_get_device_name (struct ibv_device*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  perror (char*) ; 
 int print_hca_cap (struct ibv_device*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*) ; 
 int verbose ; 

int main(int argc, char *argv[])
{
	char *ib_devname = NULL;
	int ret = 0;
	struct ibv_device **dev_list, **orig_dev_list;
	int num_of_hcas;
	int ib_port = 0;

	/* parse command line options */
	while (1) {
		int c;
		static struct option long_options[] = {
			{ .name = "ib-dev",   .has_arg = 1, .val = 'd' },
			{ .name = "ib-port",  .has_arg = 1, .val = 'i' },
			{ .name = "list",     .has_arg = 0, .val = 'l' },
			{ .name = "verbose",  .has_arg = 0, .val = 'v' },
			{ }
		};

		c = getopt_long(argc, argv, "d:i:lv", long_options, NULL);
		if (c == -1)
			break;

		switch (c) {
		case 'd':
			ib_devname = strdup(optarg);
			break;

		case 'i':
			ib_port = strtol(optarg, NULL, 0);
			if (ib_port <= 0) {
				usage(argv[0]);
				return 1;
			}
			break;

		case 'v':
			verbose = 1;
			break;

		case 'l':
			dev_list = orig_dev_list = ibv_get_device_list(&num_of_hcas);
			if (!dev_list) {
				perror("Failed to get IB devices list");
				return -1;
			}

			printf("%d HCA%s found:\n", num_of_hcas,
			       num_of_hcas != 1 ? "s" : "");

			while (*dev_list) {
				printf("\t%s\n", ibv_get_device_name(*dev_list));
				++dev_list;
			}

			printf("\n");

			ibv_free_device_list(orig_dev_list);

			return 0;

		default:
			usage(argv[0]);
			return -1;
		}
	}

	dev_list = orig_dev_list = ibv_get_device_list(NULL);
	if (!dev_list) {
		perror("Failed to get IB devices list");
		return -1;
	}

	if (ib_devname) {
		while (*dev_list) {
			if (!strcmp(ibv_get_device_name(*dev_list), ib_devname))
				break;
			++dev_list;
		}

		if (!*dev_list) {
			fprintf(stderr, "IB device '%s' wasn't found\n", ib_devname);
			return -1;
		}

		ret |= print_hca_cap(*dev_list, ib_port);
	} else {
		if (!*dev_list) {
			fprintf(stderr, "No IB devices found\n");
			return -1;
		}

		while (*dev_list) {
			ret |= print_hca_cap(*dev_list, ib_port);
			++dev_list;
		}
	}

	if (ib_devname)
		free(ib_devname);

	ibv_free_device_list(orig_dev_list);

	return ret;
}