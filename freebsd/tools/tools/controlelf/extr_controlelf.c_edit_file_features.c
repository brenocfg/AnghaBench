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
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  features ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  convert_to_feature_val (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_file_features (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 
 scalar_t__ write (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
edit_file_features(Elf *elf, int phcount, int fd, char *val)
{
	u_int32_t features;
	u_int64_t off;

	if (!get_file_features(elf, phcount, fd, &features, &off)) {
		warnx("NT_FREEBSD_FEATURE_CTL note not found");
		return (false);
	}

	if (!convert_to_feature_val(val, &features))
		return (false);

	if (lseek(fd, off, SEEK_SET) == -1 ||
	    write(fd, &features, sizeof(features)) <
	    (ssize_t)sizeof(features)) {
		warnx("error writing feature value");
		return (false);
	}
	return (true);
}