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
struct mylo_partition {scalar_t__ addr; scalar_t__ size; int flags; scalar_t__ param; } ;
struct fw_part {char* name; struct mylo_partition mylo; } ;
struct fw_block {scalar_t__ addr; scalar_t__ blocklen; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_HAVEHDR ; 
 int MAX_ARG_COUNT ; 
 int MAX_ARG_LEN ; 
 scalar_t__ MAX_FW_BLOCKS ; 
 scalar_t__ MYLO_MAX_PARTITIONS ; 
 int PARTITION_FLAG_ACTIVE ; 
 int PARTITION_FLAG_HAVEHDR ; 
 int PARTITION_FLAG_LZMA ; 
 int PARTITION_FLAG_PRELOAD ; 
 int /*<<< orphan*/  PART_NAME_LEN ; 
 int /*<<< orphan*/  errmsg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ flash_size ; 
 struct fw_block* fw_blocks ; 
 scalar_t__ fw_num_blocks ; 
 scalar_t__ fw_num_partitions ; 
 struct fw_part* fw_parts ; 
 scalar_t__ is_empty_arg (char*) ; 
 int parse_arg (char*,char*,char**) ; 
 scalar_t__ required_arg (char,char*) ; 
 scalar_t__ str2u32 (char*,scalar_t__*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int /*<<< orphan*/ ) ; 

int
parse_opt_partition(char ch, char *arg)
{
	char buf[MAX_ARG_LEN];
	char *argv[MAX_ARG_COUNT];
	int argc;
	char *p;
	struct mylo_partition *part;
	struct fw_part *fp;

	if (required_arg(ch, arg)) {
		goto err_out;
	}

	if (fw_num_partitions >= MYLO_MAX_PARTITIONS) {
		errmsg(0, "too many partitions specified");
		goto err_out;
	}

	fp = &fw_parts[fw_num_partitions++];
	part = &fp->mylo;

	argc = parse_arg(arg, buf, argv);

	/* processing partition address */
	p = argv[0];
	if (is_empty_arg(p)) {
		errmsg(0,"partition address missing in -%c %s",ch, arg);
		goto err_out;
	} else if (str2u32(p, &part->addr) != 0) {
		errmsg(0,"invalid partition address: %s", p);
		goto err_out;
	}

	/* processing partition size */
	p = argv[1];
	if (is_empty_arg(p)) {
		errmsg(0,"partition size missing in -%c %s",ch, arg);
		goto err_out;
	} else if (str2u32(p, &part->size) != 0) {
		errmsg(0,"invalid partition size: %s", p);
		goto err_out;
	}

	/* processing partition flags */
	p = argv[2];
	if (is_empty_arg(p) == 0) {
		for ( ; *p != '\0'; p++) {
			switch (*p) {
			case 'a':
				part->flags |= PARTITION_FLAG_ACTIVE;
				break;
			case 'p':
				part->flags |= PARTITION_FLAG_PRELOAD;
				break;
			case 'l':
				part->flags |= PARTITION_FLAG_LZMA;
				break;
			case 'h':
				part->flags |= PARTITION_FLAG_HAVEHDR;
				break;
			default:
				errmsg(0, "invalid partition flag \"%c\"", *p);
				goto err_out;
			}
		}
	}

	/* processing partition parameter */
	p = argv[3];
	if (is_empty_arg(p)) {
		/* set default partition parameter */
		part->param = 0;
	} else if (str2u32(p, &part->param) != 0) {
		errmsg(0,"invalid partition parameter: %s", p);
		goto err_out;
	}

	p = argv[4];
	if (is_empty_arg(p)) {
		/* set default partition parameter */
		fp->name[0] = '\0';
	} else {
		strncpy(fp->name, p, PART_NAME_LEN);
	}

#if 1
	if (part->size == 0) {
		part->size = flash_size - part->addr;
	}

	/* processing file parameter */
	p = argv[5];
	if (is_empty_arg(p) == 0) {
		struct fw_block *b;

		if (fw_num_blocks == MAX_FW_BLOCKS) {
			errmsg(0,"too many blocks specified", p);
			goto err_out;
		}
		b = &fw_blocks[fw_num_blocks++];
		b->name = strdup(p);
		b->addr = part->addr;
		b->blocklen = part->size;
		if (part->flags & PARTITION_FLAG_HAVEHDR) {
			b->flags |= BLOCK_FLAG_HAVEHDR;
		}
	}
#endif

	return 0;

err_out:
	return -1;
}