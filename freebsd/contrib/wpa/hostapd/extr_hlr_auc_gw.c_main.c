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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/  (*) ()) ; 
 int atoi (void*) ; 
 int /*<<< orphan*/  cleanup () ; 
 int /*<<< orphan*/ * db_open (char*) ; 
 char* default_socket_path ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  handle_term ; 
 int ind_len ; 
 void* milenage_file ; 
 scalar_t__ open_socket (char*) ; 
 void* optarg ; 
 int optind ; 
 int /*<<< orphan*/  os_program_deinit () ; 
 scalar_t__ os_program_init () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  process (scalar_t__) ; 
 scalar_t__ process_cmd (char*,char*,int) ; 
 scalar_t__ read_gsm_triplets (char*) ; 
 scalar_t__ read_milenage (void*) ; 
 scalar_t__ serv_sock ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* socket_path ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite_db ; 
 scalar_t__ stdout_debug ; 
 int update_milenage ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char *argv[])
{
	int c;
	char *gsm_triplet_file = NULL;
	char *sqlite_db_file = NULL;
	int ret = 0;

	if (os_program_init())
		return -1;

	socket_path = default_socket_path;

	for (;;) {
		c = getopt(argc, argv, "D:g:hi:m:s:u");
		if (c < 0)
			break;
		switch (c) {
		case 'D':
#ifdef CONFIG_SQLITE
			sqlite_db_file = optarg;
			break;
#else /* CONFIG_SQLITE */
			printf("No SQLite support included in the build\n");
			return -1;
#endif /* CONFIG_SQLITE */
		case 'g':
			gsm_triplet_file = optarg;
			break;
		case 'h':
			usage();
			return 0;
		case 'i':
			ind_len = atoi(optarg);
			if (ind_len < 0 || ind_len > 32) {
				printf("Invalid IND length\n");
				return -1;
			}
			break;
		case 'm':
			milenage_file = optarg;
			break;
		case 's':
			socket_path = optarg;
			break;
		case 'u':
			update_milenage = 1;
			break;
		default:
			usage();
			return -1;
		}
	}

	if (!gsm_triplet_file && !milenage_file && !sqlite_db_file) {
		usage();
		return -1;
	}

#ifdef CONFIG_SQLITE
	if (sqlite_db_file && (sqlite_db = db_open(sqlite_db_file)) == NULL)
		return -1;
#endif /* CONFIG_SQLITE */

	if (gsm_triplet_file && read_gsm_triplets(gsm_triplet_file) < 0)
		return -1;

	if (milenage_file && read_milenage(milenage_file) < 0)
		return -1;

	if (optind == argc) {
		serv_sock = open_socket(socket_path);
		if (serv_sock < 0)
			return -1;

		printf("Listening for requests on %s\n", socket_path);

		atexit(cleanup);
		signal(SIGTERM, handle_term);
		signal(SIGINT, handle_term);

		for (;;)
			process(serv_sock);
	} else {
		char buf[1000];
		socket_path = NULL;
		stdout_debug = 0;
		if (process_cmd(argv[optind], buf, sizeof(buf)) < 0) {
			printf("FAIL\n");
			ret = -1;
		} else {
			printf("%s\n", buf);
		}
		cleanup();
	}

#ifdef CONFIG_SQLITE
	if (sqlite_db) {
		sqlite3_close(sqlite_db);
		sqlite_db = NULL;
	}
#endif /* CONFIG_SQLITE */

	os_program_deinit();

	return ret;
}