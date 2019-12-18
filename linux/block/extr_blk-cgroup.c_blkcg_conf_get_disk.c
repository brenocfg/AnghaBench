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
struct gendisk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct gendisk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (unsigned int,unsigned int) ; 
 struct gendisk* get_gendisk (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int /*<<< orphan*/  put_disk_and_module (struct gendisk*) ; 
 char* skip_spaces (char*) ; 
 int sscanf (char*,char*,unsigned int*,unsigned int*,int*) ; 

struct gendisk *blkcg_conf_get_disk(char **inputp)
{
	char *input = *inputp;
	unsigned int major, minor;
	struct gendisk *disk;
	int key_len, part;

	if (sscanf(input, "%u:%u%n", &major, &minor, &key_len) != 2)
		return ERR_PTR(-EINVAL);

	input += key_len;
	if (!isspace(*input))
		return ERR_PTR(-EINVAL);
	input = skip_spaces(input);

	disk = get_gendisk(MKDEV(major, minor), &part);
	if (!disk)
		return ERR_PTR(-ENODEV);
	if (part) {
		put_disk_and_module(disk);
		return ERR_PTR(-ENODEV);
	}

	*inputp = input;
	return disk;
}