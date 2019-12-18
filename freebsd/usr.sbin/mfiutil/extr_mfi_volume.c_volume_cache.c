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
typedef  int /*<<< orphan*/  uint8_t ;
struct mfi_ld_props {int default_cache_policy; int disk_cache_policy; int current_cache_policy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MR_LD_CACHE_ALLOW_READ_CACHE 132 
#define  MR_LD_CACHE_ALLOW_WRITE_CACHE 131 
 int MR_LD_CACHE_READ_ADAPTIVE ; 
 int MR_LD_CACHE_READ_AHEAD ; 
 int MR_LD_CACHE_WRITE_BACK ; 
 int MR_LD_CACHE_WRITE_CACHE_BAD_BBU ; 
#define  MR_PD_CACHE_DISABLE 130 
#define  MR_PD_CACHE_ENABLE 129 
#define  MR_PD_CACHE_UNCHANGED 128 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 scalar_t__ mfi_ld_get_props (int,int /*<<< orphan*/ ,struct mfi_ld_props*) ; 
 scalar_t__ mfi_lookup_volume (int,char*,int /*<<< orphan*/ *) ; 
 int mfi_open (int,int /*<<< orphan*/ ) ; 
 int mfi_unit ; 
 char* mfi_volume_name (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int process_cache_command (int,char**,struct mfi_ld_props*) ; 
 int update_cache_policy (int,struct mfi_ld_props*,struct mfi_ld_props*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
volume_cache(int ac, char **av)
{
	struct mfi_ld_props props, new;
	int error, fd, consumed;
	uint8_t target_id;

	if (ac < 2) {
		warnx("cache: volume required");
		return (EINVAL);
	}

	fd = mfi_open(mfi_unit, O_RDWR);
	if (fd < 0) {
		error = errno;
		warn("mfi_open");
		return (error);
	}

	if (mfi_lookup_volume(fd, av[1], &target_id) < 0) {
		error = errno;
		warn("Invalid volume: %s", av[1]);
		close(fd);
		return (error);
	}

	if (mfi_ld_get_props(fd, target_id, &props) < 0) {
		error = errno;
		warn("Failed to fetch volume properties");
		close(fd);
		return (error);
	}

	if (ac == 2) {
		printf("mfi%u volume %s cache settings:\n", mfi_unit,
		    mfi_volume_name(fd, target_id));
		printf("             I/O caching: ");
		switch (props.default_cache_policy &
		    (MR_LD_CACHE_ALLOW_WRITE_CACHE |
		    MR_LD_CACHE_ALLOW_READ_CACHE)) {
		case 0:
			printf("disabled\n");
			break;
		case MR_LD_CACHE_ALLOW_WRITE_CACHE:
			printf("writes\n");
			break;
		case MR_LD_CACHE_ALLOW_READ_CACHE:
			printf("reads\n");
			break;
		case MR_LD_CACHE_ALLOW_WRITE_CACHE |
		    MR_LD_CACHE_ALLOW_READ_CACHE:
			printf("writes and reads\n");
			break;
		}
		printf("           write caching: %s\n",
		    props.default_cache_policy & MR_LD_CACHE_WRITE_BACK ?
		    "write-back" : "write-through");
		printf("write cache with bad BBU: %s\n",
		    props.default_cache_policy &
		    MR_LD_CACHE_WRITE_CACHE_BAD_BBU ? "enabled" : "disabled");
		printf("              read ahead: %s\n",
		    props.default_cache_policy & MR_LD_CACHE_READ_AHEAD ?
		    (props.default_cache_policy & MR_LD_CACHE_READ_ADAPTIVE ?
		    "adaptive" : "always") : "none");
		printf("       drive write cache: ");
		switch (props.disk_cache_policy) {
		case MR_PD_CACHE_UNCHANGED:
			printf("default\n");
			break;
		case MR_PD_CACHE_ENABLE:
			printf("enabled\n");
			break;
		case MR_PD_CACHE_DISABLE:
			printf("disabled\n");
			break;
		default:
			printf("??? %d\n", props.disk_cache_policy);
			break;
		}
		if (props.default_cache_policy != props.current_cache_policy)
			printf(
	"Cache disabled due to dead battery or ongoing battery relearn\n");
		error = 0;
	} else {
		new = props;
		av += 2;
		ac -= 2;
		while (ac > 0) {
			consumed = process_cache_command(ac, av, &new);
			if (consumed < 0) {
				close(fd);
				return (EINVAL);
			}
			av += consumed;
			ac -= consumed;
		}
		error = update_cache_policy(fd, &props, &new);
	}
	close(fd);

	return (error);
}