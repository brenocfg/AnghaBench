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
struct kvp_record {int dummy; } ;
struct TYPE_2__ {char* fname; int pool_fd; int num_blocks; size_t num_records; struct kvp_record* records; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 scalar_t__ EISDIR ; 
 int ENTRIES_PER_BLOCK ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int HV_KVP_POOL_COUNT ; 
 int /*<<< orphan*/  KVP_LOG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  MAX_FILE_NAME ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  POOL_DIR ; 
 int /*<<< orphan*/  POOL_DIR_MODE ; 
 int /*<<< orphan*/  POOL_FILE_MODE ; 
 int /*<<< orphan*/  chmod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fchmod (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ fread (struct kvp_record*,int,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* kvp_pools ; 
 struct kvp_record* malloc (int) ; 
 scalar_t__ mkdir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 
 struct kvp_record* realloc (struct kvp_record*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
kvp_file_init(void)
{
	int fd;
	FILE *filep;
	size_t records_read;
	char *fname;
	struct kvp_record *record;
	struct kvp_record *readp;
	int num_blocks;
	int i;
	int alloc_unit = sizeof(struct kvp_record) * ENTRIES_PER_BLOCK;

	if (mkdir(POOL_DIR, POOL_DIR_MODE) < 0 &&
	    (errno != EEXIST && errno != EISDIR)) {
		KVP_LOG(LOG_ERR, " Failed to create /var/db/hyperv/pool\n");
		exit(EXIT_FAILURE);
	}
	chmod(POOL_DIR, POOL_DIR_MODE); /* fix old mistake */

	for (i = 0; i < HV_KVP_POOL_COUNT; i++)
	{
		fname = kvp_pools[i].fname;
		records_read = 0;
		num_blocks = 1;
		snprintf(fname, MAX_FILE_NAME, "/var/db/hyperv/pool/.kvp_pool_%d", i);
		fd = open(fname, O_RDWR | O_CREAT, POOL_FILE_MODE);

		if (fd == -1) {
			return (1);
		}
		fchmod(fd, POOL_FILE_MODE); /* fix old mistake */


		filep = fopen(fname, "r");
		if (!filep) {
			close(fd);
			return (1);
		}

		record = malloc(alloc_unit * num_blocks);
		if (record == NULL) {
			close(fd);
			fclose(filep);
			return (1);
		}
		for ( ; ; )
		{
			readp = &record[records_read];
			records_read += fread(readp, sizeof(struct kvp_record),
				ENTRIES_PER_BLOCK,
				filep);

			if (ferror(filep)) {
				KVP_LOG(LOG_ERR, "Failed to read file, pool: %d\n",
				    i);
				exit(EXIT_FAILURE);
			}

			if (!feof(filep)) {
				/*
				 * More data to read.
				 */
				num_blocks++;
				record = realloc(record, alloc_unit *
					num_blocks);
				if (record == NULL) {
					close(fd);
					fclose(filep);
					return (1);
				}
				continue;
			}
			break;
		}
		kvp_pools[i].pool_fd = fd;
		kvp_pools[i].num_blocks = num_blocks;
		kvp_pools[i].records = record;
		kvp_pools[i].num_records = records_read;
		fclose(filep);
	}

	return (0);
}