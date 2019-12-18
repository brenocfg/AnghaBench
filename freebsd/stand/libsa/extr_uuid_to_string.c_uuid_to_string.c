#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * node; int /*<<< orphan*/  clock_seq_low; int /*<<< orphan*/  clock_seq_hi_and_reserved; int /*<<< orphan*/  time_hi_and_version; int /*<<< orphan*/  time_mid; int /*<<< orphan*/  time_low; } ;
typedef  TYPE_1__ uuid_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 char* malloc (int) ; 
 int /*<<< orphan*/  tohex (char**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_create_nil (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uuid_s_no_memory ; 
 int /*<<< orphan*/  uuid_s_ok ; 

void
uuid_to_string(const uuid_t *u, char **s, uint32_t *status)
{
	uuid_t nil;
	char *w;

	if (status != NULL)
		*status = uuid_s_ok;
	if (s == NULL)	/* Regular version does this odd-ball behavior too */
		return;
	w = *s = malloc(37);
	if (*s == NULL) {
		if (status != NULL)
			*status = uuid_s_no_memory;
		return;
	}
	if (u == NULL) {
		u = &nil;
		uuid_create_nil(&nil, NULL);
	}
	/* native */
	tohex(&w, 8, u->time_low);
	*w++ = '-';
	tohex(&w, 4, u->time_mid);
	*w++ = '-';
	tohex(&w, 4, u->time_hi_and_version);
	*w++ = '-';
	/* Big endian, so do a byte at a time */
	tohex(&w, 2, u->clock_seq_hi_and_reserved);
	tohex(&w, 2, u->clock_seq_low);
	*w++ = '-';
	tohex(&w, 2, u->node[0]);
	tohex(&w, 2, u->node[1]);
	tohex(&w, 2, u->node[2]);
	tohex(&w, 2, u->node[3]);
	tohex(&w, 2, u->node[4]);
	tohex(&w, 2, u->node[5]);
	*w++ = '\0';
}