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
struct msdos_options {int no_create; int align; int volume_id_set; int media_descriptor_set; int hidden_sectors_set; int timestamp_set; void* create_size; void* sectors_per_track; int /*<<< orphan*/  timestamp; void* size; void* reserved_sectors; void* hidden_sectors; void* num_FAT; void* media_descriptor; void* backup_sector; void* info_sector; void* drive_heads; void* floppy; void* directory_entries; int /*<<< orphan*/  block_size; void* sectors_per_cluster; void* sectors_per_fat; void* bytes_per_sector; void* OEM_string; void* volume_label; void* volume_id; int /*<<< orphan*/  fat_type; void* bootstrap; void* offset; } ;
typedef  int /*<<< orphan*/  o ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int MAXPATHLEN ; 
 char* _PATH_DEV ; 
 void* argto1 (void*,int,char*) ; 
 void* argto2 (void*,int,char*) ; 
 void* argto4 (void*,int,char*) ; 
 void* argtooff (void*,char*) ; 
 int /*<<< orphan*/  argtox (void*,int,char*) ; 
 int /*<<< orphan*/  atoi (void*) ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  get_tstamp (void*) ; 
 int getopt (int,char**,char const*) ; 
 int /*<<< orphan*/  memset (struct msdos_options*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mkfs_msdos (char const*,char const*,struct msdos_options*) ; 
 void* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 int /*<<< orphan*/  strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (void*,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
    static const char opts[] = "@:NAB:C:F:I:L:O:S:a:b:c:e:f:h:i:k:m:n:o:r:s:T:u:";
    struct msdos_options o;
    const char *fname, *dtype;
    char buf[MAXPATHLEN];
    int ch;

    memset(&o, 0, sizeof(o));

    while ((ch = getopt(argc, argv, opts)) != -1)
	switch (ch) {
	case '@':
	    o.offset = argtooff(optarg, "offset");
	    break;
	case 'N':
	    o.no_create = 1;
	    break;
	case 'A':
	    o.align = true;
	    break;
	case 'B':
	    o.bootstrap = optarg;
	    break;
	case 'C':
	    o.create_size = argtooff(optarg, "create size");
	    break;
	case 'F':
	    if (strcmp(optarg, "12") &&
		strcmp(optarg, "16") &&
		strcmp(optarg, "32"))
		errx(1, "%s: bad FAT type", optarg);
	    o.fat_type = atoi(optarg);
	    break;
	case 'I':
	    o.volume_id = argto4(optarg, 0, "volume ID");
	    o.volume_id_set = 1;
	    break;
	case 'L':
	    o.volume_label = optarg;
	    break;
	case 'O':
	    o.OEM_string = optarg;
	    break;
	case 'S':
	    o.bytes_per_sector = argto2(optarg, 1, "bytes/sector");
	    break;
	case 'a':
	    o.sectors_per_fat = argto4(optarg, 1, "sectors/FAT");
	    break;
	case 'b':
	    o.block_size = argtox(optarg, 1, "block size");
	    o.sectors_per_cluster = 0;
	    break;
	case 'c':
	    o.sectors_per_cluster = argto1(optarg, 1, "sectors/cluster");
	    o.block_size = 0;
	    break;
	case 'e':
	    o.directory_entries = argto2(optarg, 1, "directory entries");
	    break;
	case 'f':
	    o.floppy = optarg;
	    break;
	case 'h':
	    o.drive_heads = argto2(optarg, 1, "drive heads");
	    break;
	case 'i':
	    o.info_sector = argto2(optarg, 1, "info sector");
	    break;
	case 'k':
	    o.backup_sector = argto2(optarg, 1, "backup sector");
	    break;
	case 'm':
	    o.media_descriptor = argto1(optarg, 0, "media descriptor");
	    o.media_descriptor_set = 1;
	    break;
	case 'n':
	    o.num_FAT = argto1(optarg, 1, "number of FATs");
	    break;
	case 'o':
	    o.hidden_sectors = argto4(optarg, 0, "hidden sectors");
	    o.hidden_sectors_set = 1;
	    break;
	case 'r':
	    o.reserved_sectors = argto2(optarg, 1, "reserved sectors");
	    break;
	case 's':
	    o.size = argto4(optarg, 1, "file system size");
	    break;
	case 'T':
	    o.timestamp_set = 1;
	    o.timestamp = get_tstamp(optarg);
	    break;
	case 'u':
	    o.sectors_per_track = argto2(optarg, 1, "sectors/track");
	    break;
	default:
	    usage();
	}
    argc -= optind;
    argv += optind;
    if (argc < 1 || argc > 2)
	usage();
	if (o.align) {
		if (o.hidden_sectors_set)
		    errx(1, "align (-A) is incompatible with -r");
	}
    fname = *argv++;
    if (!o.create_size && !strchr(fname, '/')) {
	snprintf(buf, sizeof(buf), "%s%s", _PATH_DEV, fname);
	if (!(fname = strdup(buf)))
	    err(1, NULL);
    }
    dtype = *argv;
    return !!mkfs_msdos(fname, dtype, &o);
}