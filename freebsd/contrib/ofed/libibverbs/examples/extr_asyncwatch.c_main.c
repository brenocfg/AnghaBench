#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct option {char* name; int has_arg; char val; } ;
struct ibv_device {int dummy; } ;
struct ibv_context {int async_fd; } ;
struct TYPE_2__ {int port_num; } ;
struct ibv_async_event {int event_type; TYPE_1__ element; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWITCH_FALLTHROUGH ; 
 int /*<<< orphan*/  _IOLBF ; 
 char* event_name_str (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getopt_long (int,char**,char*,struct option*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibv_ack_async_event (struct ibv_async_event*) ; 
 scalar_t__ ibv_get_async_event (struct ibv_context*,struct ibv_async_event*) ; 
 struct ibv_device** ibv_get_device_list (int /*<<< orphan*/ *) ; 
 char* ibv_get_device_name (struct ibv_device*) ; 
 struct ibv_context* ibv_open_device (struct ibv_device*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,int,...) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strdupa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char *argv[])
{
	struct ibv_device **dev_list;
	struct ibv_context *context;
	struct ibv_async_event event;
	char   *ib_devname = NULL;
	int i = 0;

	/* Force line-buffering in case stdout is redirected */
	setvbuf(stdout, NULL, _IOLBF, 0);

	while (1) {
		int ret = 1;
		int c;
		static struct option long_options[] = {
			{ .name = "ib-dev",    .has_arg = 1, .val = 'd' },
			{ .name = "help",      .has_arg = 0, .val = 'h' },
			{}
		};

		c = getopt_long(argc, argv, "d:h", long_options, NULL);
		if (c == -1)
			break;
		switch (c) {
		case 'd':
			ib_devname = strdupa(optarg);
			break;
		case 'h':
			ret = 0;
			SWITCH_FALLTHROUGH;
		default:
			usage(argv[0]);
			return ret;
		}
	}
	dev_list = ibv_get_device_list(NULL);
	if (!dev_list) {
		perror("Failed to get IB devices list");
		return 1;
	}
	if (ib_devname) {
		for (; dev_list[i]; ++i) {
			if (!strcmp(ibv_get_device_name(dev_list[i]), ib_devname))
				break;
		}
	}

	if (!dev_list[i]) {
		fprintf(stderr, "IB device %s not found\n",
			ib_devname ? ib_devname : "");
		return 1;
	}

	context = ibv_open_device(dev_list[i]);
	if (!context) {
		fprintf(stderr, "Couldn't get context for %s\n",
			ibv_get_device_name(dev_list[i]));
		return 1;
	}

	printf("%s: async event FD %d\n",
	       ibv_get_device_name(dev_list[i]), context->async_fd);

	while (1) {
		if (ibv_get_async_event(context, &event))
			return 1;

		printf("  event_type %s (%d), port %d\n",
		       event_name_str(event.event_type),
		       event.event_type, event.element.port_num);

		ibv_ack_async_event(&event);
	}

	return 0;
}