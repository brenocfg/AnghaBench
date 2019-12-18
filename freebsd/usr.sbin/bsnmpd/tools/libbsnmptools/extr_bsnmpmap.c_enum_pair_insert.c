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
struct enum_pairs {int dummy; } ;
struct enum_pair {int enum_val; int /*<<< orphan*/ * enum_str; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (struct enum_pairs*,struct enum_pair*,int /*<<< orphan*/ ) ; 
 struct enum_pair* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct enum_pair*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int32_t
enum_pair_insert(struct enum_pairs *headp, int32_t enum_val, char *enum_str)
{
	struct enum_pair *e_new;

	if ((e_new = calloc(1, sizeof(struct enum_pair))) == NULL) {
		syslog(LOG_ERR, "calloc() failed: %s", strerror(errno));
		return (-1);
	}

	if ((e_new->enum_str = strdup(enum_str)) == NULL) {
		syslog(LOG_ERR, "strdup() failed: %s", strerror(errno));
		free(e_new);
		return (-1);
	}

	e_new->enum_val = enum_val;
	STAILQ_INSERT_TAIL(headp, e_new, link);

	return (1);

}