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
struct switch_val {int port_vlan; } ;
struct switch_dev {int ports; int vlans; } ;
struct switch_attr {int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  CMD_GET 133 
#define  CMD_HELP 132 
#define  CMD_LOAD 131 
 int CMD_NONE ; 
#define  CMD_PORTMAP 130 
#define  CMD_SET 129 
#define  CMD_SHOW 128 
 int /*<<< orphan*/  SWITCH_TYPE_NOVAL ; 
 int /*<<< orphan*/  SWLIB_ATTR_GROUP_GLOBAL ; 
 int /*<<< orphan*/  SWLIB_ATTR_GROUP_PORT ; 
 int /*<<< orphan*/  SWLIB_ATTR_GROUP_VLAN ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  list_attributes (struct switch_dev*) ; 
 int /*<<< orphan*/  nl_perror (int,char*) ; 
 int /*<<< orphan*/  print_attr_val (struct switch_attr*,struct switch_val*) ; 
 int /*<<< orphan*/  print_usage () ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  show_global (struct switch_dev*) ; 
 int /*<<< orphan*/  show_port (struct switch_dev*,int) ; 
 int /*<<< orphan*/  show_vlan (struct switch_dev*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  swconfig_load_uci (struct switch_dev*,char*) ; 
 struct switch_dev* swlib_connect (char*) ; 
 int /*<<< orphan*/  swlib_free_all (struct switch_dev*) ; 
 int swlib_get_attr (struct switch_dev*,struct switch_attr*,struct switch_val*) ; 
 int /*<<< orphan*/  swlib_list () ; 
 struct switch_attr* swlib_lookup_attr (struct switch_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  swlib_print_portmap (struct switch_dev*,char*) ; 
 int /*<<< orphan*/  swlib_scan (struct switch_dev*) ; 
 int swlib_set_attr_string (struct switch_dev*,struct switch_attr*,int,char*) ; 

int main(int argc, char **argv)
{
	int retval = 0;
	struct switch_dev *dev;
	struct switch_attr *a;
	struct switch_val val;
	int i;

	int cmd = CMD_NONE;
	char *cdev = NULL;
	int cport = -1;
	int cvlan = -1;
	char *ckey = NULL;
	char *cvalue = NULL;
	char *csegment = NULL;

	if((argc == 2) && !strcmp(argv[1], "list")) {
		swlib_list();
		return 0;
	}

	if(argc < 4)
		print_usage();

	if(strcmp(argv[1], "dev"))
		print_usage();

	cdev = argv[2];

	for(i = 3; i < argc; i++)
	{
		char *arg = argv[i];
		if (cmd != CMD_NONE) {
			print_usage();
		} else if (!strcmp(arg, "port") && i+1 < argc) {
			cport = atoi(argv[++i]);
		} else if (!strcmp(arg, "vlan") && i+1 < argc) {
			cvlan = atoi(argv[++i]);
		} else if (!strcmp(arg, "help")) {
			cmd = CMD_HELP;
		} else if (!strcmp(arg, "set") && i+1 < argc) {
			cmd = CMD_SET;
			ckey = argv[++i];
			if (i+1 < argc)
				cvalue = argv[++i];
		} else if (!strcmp(arg, "get") && i+1 < argc) {
			cmd = CMD_GET;
			ckey = argv[++i];
		} else if (!strcmp(arg, "load") && i+1 < argc) {
			if ((cport >= 0) || (cvlan >= 0))
				print_usage();
			cmd = CMD_LOAD;
			ckey = argv[++i];
		} else if (!strcmp(arg, "portmap")) {
			if (i + 1 < argc)
				csegment = argv[++i];
			cmd = CMD_PORTMAP;
		} else if (!strcmp(arg, "show")) {
			cmd = CMD_SHOW;
		} else {
			print_usage();
		}
	}

	if (cmd == CMD_NONE)
		print_usage();
	if (cport > -1 && cvlan > -1)
		print_usage();

	dev = swlib_connect(cdev);
	if (!dev) {
		fprintf(stderr, "Failed to connect to the switch. Use the \"list\" command to see which switches are available.\n");
		return 1;
	}

	swlib_scan(dev);

	if (cmd == CMD_GET || cmd == CMD_SET) {
		if(cport > -1)
			a = swlib_lookup_attr(dev, SWLIB_ATTR_GROUP_PORT, ckey);
		else if(cvlan > -1)
			a = swlib_lookup_attr(dev, SWLIB_ATTR_GROUP_VLAN, ckey);
		else
			a = swlib_lookup_attr(dev, SWLIB_ATTR_GROUP_GLOBAL, ckey);

		if(!a)
		{
			fprintf(stderr, "Unknown attribute \"%s\"\n", ckey);
			retval = -1;
			goto out;
		}
	}

	switch(cmd)
	{
	case CMD_SET:
		if ((a->type != SWITCH_TYPE_NOVAL) &&
				(cvalue == NULL))
			print_usage();

		if(cvlan > -1)
			cport = cvlan;

		retval = swlib_set_attr_string(dev, a, cport, cvalue);
		if (retval < 0)
		{
			nl_perror(-retval, "Failed to set attribute");
			goto out;
		}
		break;
	case CMD_GET:
		if(cvlan > -1)
			val.port_vlan = cvlan;
		if(cport > -1)
			val.port_vlan = cport;
		retval = swlib_get_attr(dev, a, &val);
		if (retval < 0)
		{
			nl_perror(-retval, "Failed to get attribute");
			goto out;
		}
		print_attr_val(a, &val);
		putchar('\n');
		break;
	case CMD_LOAD:
		swconfig_load_uci(dev, ckey);
		break;
	case CMD_HELP:
		list_attributes(dev);
		break;
	case CMD_PORTMAP:
		swlib_print_portmap(dev, csegment);
		break;
	case CMD_SHOW:
		if (cport >= 0 || cvlan >= 0) {
			if (cport >= 0)
				show_port(dev, cport);
			else
				show_vlan(dev, cvlan, false);
		} else {
			show_global(dev);
			for (i=0; i < dev->ports; i++)
				show_port(dev, i);
			for (i=0; i < dev->vlans; i++)
				show_vlan(dev, i, true);
		}
		break;
	}

out:
	swlib_free_all(dev);
	return retval;
}