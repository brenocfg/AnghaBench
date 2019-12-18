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
struct lun {int l_ctl_lun; int /*<<< orphan*/  l_options; int /*<<< orphan*/  l_name; struct conf* l_conf; } ;
struct conf {int /*<<< orphan*/  conf_luns; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct lun*,int /*<<< orphan*/ ) ; 
 struct lun* calloc (int,int) ; 
 int /*<<< orphan*/  checked_strdup (char const*) ; 
 int /*<<< orphan*/  l_next ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  log_warnx (char*,char const*) ; 
 struct lun* lun_find (struct conf*,char const*) ; 

struct lun *
lun_new(struct conf *conf, const char *name)
{
	struct lun *lun;

	lun = lun_find(conf, name);
	if (lun != NULL) {
		log_warnx("duplicated lun \"%s\"", name);
		return (NULL);
	}

	lun = calloc(1, sizeof(*lun));
	if (lun == NULL)
		log_err(1, "calloc");
	lun->l_conf = conf;
	lun->l_name = checked_strdup(name);
	TAILQ_INIT(&lun->l_options);
	TAILQ_INSERT_TAIL(&conf->conf_luns, lun, l_next);
	lun->l_ctl_lun = -1;

	return (lun);
}