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
struct sshkey {scalar_t__ type; } ;
struct sshbuf {int dummy; } ;

/* Variables and functions */
 int C2S ; 
 scalar_t__ KEY_UNSPEC ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int S2C ; 
 int /*<<< orphan*/  SYSLOG_FACILITY_USER ; 
 int /*<<< orphan*/  SYSLOG_LEVEL_DEBUG3 ; 
 int /*<<< orphan*/  SYSLOG_LEVEL_INFO ; 
 int /*<<< orphan*/  _IONBF ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  badusage (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int do_debug ; 
 int /*<<< orphan*/  do_kex_with_key (char const*,struct sshkey*,int*,int*,int,int,char const*,struct sshbuf*) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  kex_names_valid (char const*) ; 
 int /*<<< orphan*/  log_init (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssh_err (int) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 struct sshbuf* sshbuf_new () ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 int sshkey_load_file (int,struct sshbuf*) ; 
 int sshkey_load_private_type_fd (int,scalar_t__,int /*<<< orphan*/ *,struct sshkey**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	int ch, fd, r;
	int count_flag = 0, dump_flag = 0, replace_flag = 0;
	int packet_index = -1, direction = -1;
	int s2c = 0, c2s = 0; /* packet counts */
	const char *kex = NULL, *kpath = NULL, *data_path = NULL;
	struct sshkey *key = NULL;
	struct sshbuf *replace_data = NULL;

	setvbuf(stdout, NULL, _IONBF, 0);
	while ((ch = getopt(argc, argv, "hcdrvD:f:K:k:i:")) != -1) {
		switch (ch) {
		case 'h':
			usage();
			return 0;
		case 'c':
			count_flag = 1;
			break;
		case 'd':
			dump_flag = 1;
			break;
		case 'r':
			replace_flag = 1;
			break;
		case 'v':
			do_debug = 1;
			break;

		case 'D':
			if (strcasecmp(optarg, "s2c") == 0)
				direction = S2C;
			else if (strcasecmp(optarg, "c2s") == 0)
				direction = C2S;
			else
				badusage("Invalid direction (-D)");
			break;
		case 'f':
			data_path = optarg;
			break;
		case 'K':
			kex = optarg;
			break;
		case 'k':
			kpath = optarg;
			break;
		case 'i':
			packet_index = atoi(optarg);
			if (packet_index < 0)
				badusage("Invalid packet index");
			break;
		default:
			badusage("unsupported flag");
		}
	}
	argc -= optind;
	argv += optind;

	log_init(argv[0], do_debug ? SYSLOG_LEVEL_DEBUG3 : SYSLOG_LEVEL_INFO,
	    SYSLOG_FACILITY_USER, 1);

	/* Must select a single mode */
	if ((count_flag + dump_flag + replace_flag) != 1)
		badusage("Must select one mode: -c, -d or -r");
	/* KEX type is mandatory */
	if (kex == NULL || !kex_names_valid(kex) || strchr(kex, ',') != NULL)
		badusage("Missing or invalid kex type (-K flag)");
	/* Valid key is mandatory */
	if (kpath == NULL)
		badusage("Missing private key (-k flag)");
	if ((fd = open(kpath, O_RDONLY)) == -1)
		err(1, "open %s", kpath);
	if ((r = sshkey_load_private_type_fd(fd, KEY_UNSPEC, NULL,
	    &key, NULL)) != 0)
		errx(1, "Unable to load key %s: %s", kpath, ssh_err(r));
	close(fd);
	/* XXX check that it is a private key */
	/* XXX support certificates */
	if (key == NULL || key->type == KEY_UNSPEC)
		badusage("Invalid key file (-k flag)");

	/* Replace (fuzz) mode */
	if (replace_flag) {
		if (packet_index == -1 || direction == -1 || data_path == NULL)
			badusage("Replace (-r) mode must specify direction "
			    "(-D) packet index (-i) and data path (-f)");
		if ((fd = open(data_path, O_RDONLY)) == -1)
			err(1, "open %s", data_path);
		replace_data = sshbuf_new();
		if ((r = sshkey_load_file(fd, replace_data)) != 0)
			errx(1, "read %s: %s", data_path, ssh_err(r));
		close(fd);
	}

	/* Dump mode */
	if (dump_flag) {
		if (packet_index == -1 || direction == -1 || data_path == NULL)
			badusage("Dump (-d) mode must specify direction "
			    "(-D), packet index (-i) and data path (-f)");
	}

	/* Count mode needs no further flags */

	do_kex_with_key(kex, key, &c2s, &s2c,
	    direction, packet_index,
	    dump_flag ? data_path : NULL,
	    replace_flag ? replace_data : NULL);
	sshkey_free(key);
	sshbuf_free(replace_data);

	if (count_flag) {
		printf("S2C: %d\n", s2c);
		printf("C2S: %d\n", c2s);
	}

	return 0;
}