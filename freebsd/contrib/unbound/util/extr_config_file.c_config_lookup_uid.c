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
struct passwd {int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_uid; } ;
struct config_file {scalar_t__* username; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfg_gid ; 
 int /*<<< orphan*/  cfg_uid ; 
 struct passwd* getpwnam (scalar_t__*) ; 

void config_lookup_uid(struct config_file* cfg)
{
#ifdef HAVE_GETPWNAM
	/* translate username into uid and gid */
	if(cfg->username && cfg->username[0]) {
		struct passwd *pwd;
		if((pwd = getpwnam(cfg->username)) != NULL) {
			cfg_uid = pwd->pw_uid;
			cfg_gid = pwd->pw_gid;
		}
	}
#else
	(void)cfg;
#endif
}